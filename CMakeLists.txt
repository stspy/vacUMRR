cmake_minimum_required(VERSION 2.6)

# Set the installation directory of the binary file
IF(WIN32)
   SET(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory")
   MESSAGE(STATUS "WIN32")
ELSE()
   SET(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "Installation Directory")
ENDIF()
  
#
# Set the project name.
#
PROJECT (NetSend-v0.1.0_QT)

SET (EXECUTABLE_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/bin CACHE INTERNAL
  "Where to put the executables")

SET (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib CACHE INTERNAL
  "Where to put the libraries")

SET (DEBUG 1)  
 

IF(WIN32)
   # Set the prefix for the debug library
   SET (VAC_DEBUG_PREFIX "_d")
ELSE()
   SET (VAC_DEBUG_PREFIX "") 
ENDIF()

#IF (DEBUG)
#	SET (ENV{VTK_DIR} D:/ProgramFiles/VTK/VTK_Win64_Debug)
#ELSE ()
#	SET (ENV{VTK_DIR} D:/ProgramFiles/VTK/VTK_Win64_Release)
#ENDIF ()

SUBDIRS ( 
  Apps 
  ExtLibs
  VAClass
  )

# Open the property setting
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
SET_PROPERTY(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMakeTargets")


INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})


# Add the mysql path
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/ExtLibs/mysql/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/ExtLibs/mysql/lib)

# Set the mysql library
SET (LIB_MYSQL "libmysql" "libmysqld" "mysqlclient" "mysqlserver" "mysqlservices")

# Add the dataparse path
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/ExtLibs/dataparse/include)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/ExtLibs/dataparse/lib)

# Add the include path for jason
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/ExtLibs/lib_json)

# Add the include path for vacNetRec
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/VAClass/vacNetRec)

# Add the include path for vacNetSend
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/VAClass/vacNetSend)

# Add the include path for vacRadarCommon
INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/VAClass/OtherHeader)


# Add the ptread library
IF (WIN32)
   INCLUDE_DIRECTORIES (${PROJECT_SOURCE_DIR}/ExtLibs/pthread-win32/include)
   LINK_DIRECTORIES (${PROJECT_SOURCE_DIR}/ExtLibs/pthread-win32/lib/x86)
   SET (LIB_PTHREAD "pthreadVSE2")
ELSE ()
   SET (LIB_PTHREAD "")
ENDIF ()

# For QT
FIND_PACKAGE (Qt4 REQUIRED)
INCLUDE (${QT_USE_FILE})
ADD_DEFINITIONS (${QT_DEFINITIONS})










 
  
