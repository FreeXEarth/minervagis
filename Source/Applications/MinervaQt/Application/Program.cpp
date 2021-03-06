
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2007, Perry L Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Helios program class. Handles startup, shutdown, and branding.
//
///////////////////////////////////////////////////////////////////////////////

#include "Program.h"
#include "Application.h"
#include "MainWindow.h"

#include "Usul/App/Application.h"
#include "Usul/Convert/Convert.h"
#include "Usul/CommandLine/Arguments.h"
#include "Usul/Components/Manager.h"
#include "Usul/Errors/AssertPolicy.h"
#include "Usul/Errors/CompositePolicy.h"
#include "Usul/Errors/ThrowingPolicy.h"
#include "Usul/Errors/InvalidParameter.h"
#include "Usul/Errors/PureVirtualCall.h"
#include "Usul/Errors/UnhandledException.h"
#include "Usul/Exceptions/Exception.h"
#include "Usul/File/Path.h"
#include "Usul/Functions/SafeCall.h"
#include "Usul/Jobs/Manager.h"
#include "Usul/IO/Redirect.h"
#include "Usul/IO/StreamSink.h"
#include "Usul/Registry/Database.h"
#include "Usul/Signals/Actions.h"
#include "Usul/Signals/Handler.h"
#include "Usul/Strings/Case.h"
#include "Usul/Strings/Format.h"
#include "Usul/System/Environment.h"
#include "Usul/System/Host.h"
#include "Usul/Threads/Mutex.h"
#include "Usul/Threads/Named.h"
#include "Usul/User/Directory.h"

#include "boost/concept_check.hpp"

#include <fstream>
#include <sstream>


///////////////////////////////////////////////////////////////////////////////
//
//  Need this to live longer than anything.
//
///////////////////////////////////////////////////////////////////////////////

namespace Helper
{
  // Trapping errors.
  typedef Usul::Errors::ThrowingPolicy < std::runtime_error > ThrowingPolicy;
  typedef Usul::Errors::CompositePolicy < Usul::Errors::AssertPolicy, ThrowingPolicy > CompositePolicy;
  Usul::Errors::PureVirtualCall < CompositePolicy > pureCallAction;
  Usul::Errors::UnhandledException < CompositePolicy > unhandledException;
  Usul::Errors::InvalidParameter < CompositePolicy > invalidParameterAction;

  // Trapping signals.
  typedef Usul::Signals::Actions::PrintMessage PrintMessage;
  typedef Usul::Signals::Actions::PrintStackTrace PrintStackTrace;
  typedef Usul::Signals::Actions::Pair<PrintMessage,PrintStackTrace> PrintPair;
  typedef Usul::Signals::Actions::Throw<Usul::Exceptions::Exception> Throw;
  typedef Usul::Signals::Actions::Pair<PrintPair,Throw> SignalAction;
  USUL_DECLARE_SIGNAL_HANDLER ( SignalAction, SegmentationViolation );
  USUL_DECLARE_SIGNAL_HANDLER ( SignalAction, AbortSignal );
  USUL_DECLARE_SIGNAL_HANDLER ( SignalAction, FloatingPointException  );
  USUL_DECLARE_SIGNAL_HANDLER ( SignalAction, BusError  );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Clean up after the application.
//
///////////////////////////////////////////////////////////////////////////////

namespace Helper
{
  void cleanup()
  {
    // Release all plugins.
    Usul::Components::Manager::instance().clear ( &std::cout );

    // Clear the map of named threads.
    Usul::Threads::Named::clear();

    // Clear the registry.
    Usul::Registry::Database::destroy();
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Helper object to clean up after the application.
//
///////////////////////////////////////////////////////////////////////////////

namespace Helper
{
  struct Clean
  {
    ~Clean()
    {
      Usul::Functions::safeCall ( &Helper::cleanup, "2129726739" );
    }
  };
}


///////////////////////////////////////////////////////////////////////////////
//
//  Called when there is an unhandled exception.
//
///////////////////////////////////////////////////////////////////////////////

namespace Helper
{
  void _unhandledException()
  {
    std::cout << "Error 1098096861: Unhandled exception" << std::endl;

    // Abort if this is the main thread, otherwise just exit the thread.
    if ( Usul::Threads::Named::instance().is ( Usul::Threads::Names::MAIN ) )
    {
      // Restore the default signal handler so we don't get an infinite loop.
      Usul::Signals::restoreDefault ( Usul::Signals::ID::AbortSignal );
      ::abort();
    }
    else
    {
      #ifdef __GNUC__
      // This will likely leave a few mutexes locked...
      ::pthread_exit ( 0x0 );
      #else
      // Exit the thread.  The -1 is the return code.
      ::ExitThread ( -1 );
      #endif
    }
  }
}


///////////////////////////////////////////////////////////////////////////////
//
//  Run the application.
//
///////////////////////////////////////////////////////////////////////////////

void Program::run ( int argc, char **argv,
                    const std::string &program, 
                    const std::string &version, 
                    const std::string &vendor, 
                    const std::string &url, 
                    const std::string &icon, 
                    const std::string &splash,
                    unsigned int poolSize,
                    int &result )
{
  // Set the handler for unhandled exceptions.
  std::set_terminate ( &Helper::_unhandledException );

  // Set command-line arguments.
  Usul::CommandLine::Arguments::instance().set ( argc, argv );
  
  // Make job manager.
  Usul::Jobs::Manager::init ( Usul::Strings::format ( program, " Job Manager Singleton" ), poolSize );

  // Set splash image.
  Usul::App::Application::instance().splashImage ( splash );
  
  // Set information.
  Usul::App::Application::instance().vendor ( vendor );
  Usul::App::Application::instance().program ( program );

  // Get persistant directory and make sure it exists.
  const std::string persistantDir ( Usul::User::Directory::vendor ( vendor, true ) + program + "/" );
  boost::filesystem::create_directories ( persistantDir );

  // Get the machine name.
  const std::string machine ( Usul::System::Host::name() );

  // Redirect standard out and error to a file.
  const std::string output ( persistantDir + machine + "_stdout.txt" );
  boost::filesystem::remove ( output );
  Usul::IO::Redirect redirect ( output ); boost::ignore_unused_variable_warning ( redirect );

  // Print welcome message.
  std::ostringstream out;
  out << "Welcome to " << program << ' ' << version << std::endl;
  out << "Built on " << Usul::Strings::formatDate ( __DATE__ ) << " at " << __TIME__ << std::endl;

  // Set job manager's log file.
  const std::string logFile ( persistantDir + machine + "_jobs.csv" );
  Usul::Jobs::Manager::instance().logSet ( new Usul::File::Log ( logFile, false ) );

  // Initialize singleton of named threads.
  Usul::Threads::Named::instance().set ( Usul::Threads::Names::MAIN );
  
  // We want the above objects to live longer than the application.
  {
    // For cleaning.
    Helper::Clean clean; boost::ignore_unused_variable_warning ( clean );

    // Declare application.
    CadKit::Helios::Core::Application app ( argc, argv );

    // Call quit when the last window closes. (Not sure if this is needed...)
    app.connect ( &app, SIGNAL ( lastWindowClosed() ), &app, SLOT ( quit() ) );

    // We want the application to live longer than the main window.
    {
      // Declare the main window.
      MainWindow mw ( vendor, url, program, icon, output, out.str(), true );

      // Main window needs to live longer than the stream listener.
      {
        // Now we can print this to stdout. Note: this isn't fool-proof. 
        // If some other code printed to stdout or stderr before the sink's 
        // listener was set, it will go to the file but not the text window.
        std::cout << out.str() << std::flush;

        // Print additional info if we are supposed to.
        const std::string printDebugEnvName ( Usul::Strings::upperCase ( program ) + "_PRINT_DEBUG_INFO" );
        const std::string printDebugEnvValue ( Usul::System::Environment::get ( printDebugEnvName ) );
        if ( true == Usul::Convert::Type<std::string,bool>::convert ( printDebugEnvValue ) ) 
        {
          std::cout << "Text output: " << output << std::endl;
          std::cout << "Settings file: " << mw.settingsFileName() << std::flush;
        }

        // Load the plugins.
        mw.loadPlugins ( mw.pluginFile() );
        mw.printPlugins();

        // Restore the main window's state.
        mw.restoreDockWindows();

        // Hide the splash screen and show the main window.
        mw.hideSplashScreen();
        mw.show();

        // Parse the command-line.
        mw.parseCommandLine ( argc, argv );

        // Run the application.
        result = app.exec();
      }
    }
  }
}
