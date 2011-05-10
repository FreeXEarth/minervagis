
///////////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2002, Perry L. Miller IV
//  All rights reserved.
//  BSD License: http://www.opensource.org/licenses/bsd-license.html
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
//  Class that queries machine memory.
//
///////////////////////////////////////////////////////////////////////////////

#include "Usul/System/Memory.h"

#include <sstream>

#ifdef _MSC_VER
# define NOMINMAX
# define WIN32_LEAN_AND_MEAN
# include <windows.h> // For GetComputerName()
#endif

#ifdef __APPLE__
#include <sys/sysctl.h>
#include <stdio.h>
#include <mach/mach_host.h>
#include <mach/mach.h>
#include <mach/mach_types.h>
#endif

#ifdef __linux
#include <sys/sysinfo.h>
#endif

using namespace Usul;
using namespace Usul::System;


#ifdef __APPLE__
namespace Darwin {
  static void                     getVMStat (vm_statistics_t vmstat);
  static int                      getPageSize();
  static long long int            getPhysicalMemory(); 
  static long long int            getUsedMemory();
  static long long int            getAvailableMemory();
}
#endif


///////////////////////////////////////////////////////////////////////////////
//
//  Get the memory.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Types::Uint64 Memory::totalPhysical()
{
#ifdef _MSC_VER

  ::MEMORYSTATUS status;
  ::GlobalMemoryStatus ( &status );
  return status.dwTotalPhys;
  
#elif __APPLE__
  
  return ::Darwin::getPhysicalMemory();  
  
#elif __linux

  struct sysinfo info;
  sysinfo ( &info );
  return info.totalram;
  
#else
  TODO FIX ME

#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the memory.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Types::Uint64 Memory::totalVirtual()
{
#ifdef _MSC_VER

  ::MEMORYSTATUS status;
  ::GlobalMemoryStatus ( &status );
  return status.dwTotalVirtual;

#elif __APPLE__
#if 0
  //This fails on OS X 10.3.9
  //This isn't really correct.. should not be used.
    struct xsw_usage swapusage;
    
    int mib[2];
    size_t len;
    mib[0] = CTL_VM;
    mib[1] = VM_SWAPUSAGE;
    len = sizeof(swapusage);
    sysctl(mib, 2, &swapusage, &len, NULL, 0);
    return static_cast< Usul::Types::Uint64 > ( swapusage.xsu_total );
#endif
  return 0;
#elif __linux

  struct sysinfo info;
  sysinfo ( &info );
  return info.totalswap;
  
#else
  TODO  FIX ME
#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the memory.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Types::Uint64 Memory::availablePhysical()
{
#ifdef _MSC_VER

  ::MEMORYSTATUS status;
  ::GlobalMemoryStatus ( &status );
  return status.dwAvailPhys;

#elif __APPLE__
  
  return ::Darwin::getAvailableMemory();

#elif __linux

  struct sysinfo info;
  sysinfo ( &info );
  return info.freeram;
  
#else

  TODO FIX ME
  
#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the memory.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Types::Uint64 Memory::availableVirtual()
{
#ifdef _MSC_VER

  ::MEMORYSTATUS status;
  ::GlobalMemoryStatus ( &status );
  return status.dwAvailVirtual;

#elif __APPLE__
#if 0
  This is not correct and should not be used
    struct xsw_usage swapusage;
    int mib[2];
    size_t len;
    mib[0] = CTL_VM;
    mib[1] = VM_SWAPUSAGE;
    len = sizeof(swapusage);
    sysctl(mib, 2, &swapusage, &len, NULL, 0);
    return static_cast< Usul::Types::Uint64 > ( swapusage.xsu_avail );
#endif   
  return 0;
 #elif __linux

  struct sysinfo info;
  sysinfo ( &info );
  return info.freeswap;
  
#else

 TODO FIX ME

#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the memory.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Types::Uint64 Memory::usedPhysical()
{
#ifdef __APPLE__
  
  return ::Darwin::getUsedMemory();

#else

  return ( Memory::totalPhysical() - Memory::availablePhysical() );

#endif
}


///////////////////////////////////////////////////////////////////////////////
//
//  Get the memory.
//
///////////////////////////////////////////////////////////////////////////////

Usul::Types::Uint64 Memory::usedVirtual()
{
  return ( Memory::totalVirtual() - Memory::availableVirtual() );
}


///////////////////////////////////////////////////////////////////////////////
//
//  Return a formatted string.
//
///////////////////////////////////////////////////////////////////////////////

std::string Memory::formatPhysical()
{
  const Usul::Types::Uint64 toKB ( 1024 );
  std::ostringstream out;
  out << "Memory Used: " << Memory::usedPhysical()      / toKB 
      << ", Available: " << Memory::availablePhysical() / toKB 
      << ", Total: "     << Memory::totalPhysical()     / toKB;
  return out.str();
}


#ifdef __APPLE__
namespace Darwin {

void getVMStat (vm_statistics_t vmstat)
{
	unsigned int count = HOST_VM_INFO_COUNT;
	if ( host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t) vmstat, &count) != KERN_SUCCESS )
		printf("Failed to get VM statistics.");
}

int getPageSize()
{
  int mib[2];
  size_t len;
  int pageSize;
  mib[0] = CTL_HW;
  mib[1] = HW_PAGESIZE;
  len = sizeof(pageSize);
  sysctl(mib, 2, &pageSize, &len, NULL, 0);
  return pageSize;
}

long long int getPhysicalMemory() 
{
  int mib[2];
  size_t len;
   int physmem;
  mib[0] = CTL_HW;
  mib[1] = HW_PHYSMEM;
  len = sizeof(physmem);
  sysctl(mib, 2, &physmem, &len, NULL, 0);
  return physmem;
}

long long int getUsedMemory()
{
  long long int total;
  vm_statistics_data_t	vmstat;
  ::Darwin::getVMStat (&vmstat);
  total = vmstat.wire_count + vmstat.active_count + vmstat.inactive_count ;
  total = total * ::Darwin::getPageSize();
  return (long long int)total;
}

long long int getAvailableMemory()
{
  vm_statistics_data_t	vmstat;
  ::Darwin::getVMStat (&vmstat);
  return (long long int) (vmstat.free_count * ::Darwin::getPageSize() );
}

}

#endif
