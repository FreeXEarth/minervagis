
INCLUDE_DIRECTORIES ( ${SPATIALITE_INCLUDES} )

ADD_DEFINITIONS ( "-D_COMPILING_SQL_LITE_WRAP" )

INCLUDE_DIRECTORIES ( ${SQLITE_INCLUDE_DIR} )

IF(SPATIALITE_FOUND)
	INCLUDE_DIRECTORIES ( ${SPATIALITE_INCLUDE_DIR} )
ENDIF()

SET ( HEADERS
./Connection.h
./Result.h
./Types.h
./Internal.h
./Transaction.h
./Binder.h
./Export.h
./Input.h
)

SET ( SOURCES
./Result.cpp
./Binder.cpp
./Connection.cpp
)

IF(SPATIALITE_FOUND)
	ADD_DEFINITIONS( "-DHAVE_SPATIALITE" )
ENDIF()

SET ( TARGET_NAME DatabaseSQLite )

# Create a Shared Library
ADD_LIBRARY( ${TARGET_NAME} SHARED ${HEADERS} ${SOURCES} )

# Add a library
CADKIT_ADD_LIBRARY ( ${TARGET_NAME} )

# Link the Library
LINK_CADKIT( ${TARGET_NAME} Usul )

TARGET_LINK_LIBRARIES( ${TARGET_NAME} ${SQLITE_LIBRARY} )
IF(SPATIALITE_FOUND)
	TARGET_LINK_LIBRARIES( ${TARGET_NAME} ${SPATILITE_LIBRARY} )
ENDIF()

install ( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include/cadkit/Database
            PATTERN "*.h"	
            PATTERN "*.cpp" EXCLUDE
            PATTERN ".svn" EXCLUDE
            PATTERN "Debug" EXCLUDE
            PATTERN "Release" EXCLUDE
            PATTERN "CMakeLists.txt" EXCLUDE
            PATTERN "*~" EXCLUDE		  
            PATTERN "*.vcproj" EXCLUDE )
