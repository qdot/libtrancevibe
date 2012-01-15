######################################################################################
# CMake directives
######################################################################################

#Require 2.6 or higher. 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0 FATAL_ERROR)

#setting link directory policy

IF(COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

# Add our repository cmake_modules directory
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

# Add local macros and project options
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/BuildSysCmakeLib.cmake)

######################################################################################
# Project declaration and options
######################################################################################

#Project declaration

PROJECT(LIBTRANCEVIBE)
INITIALIZE_BUILD()

#Common Options

OPTION_LIBRARY_BUILD_STATIC(ON)
#We can't build shared on MSVC yet
IF(NOT MSVC)
  OPTION_LIBRARY_BUILD_SHARED(OFF)
ENDIF(NOT MSVC)

#Project specific options
OPTION(BUILD_EXAMPLES "Build libtrancevibe examples" ON)

######################################################################################
# Project specific package finding
######################################################################################

# IF(NOT WIN32)
#   FIND_PACKAGE(libusb-1.0 REQUIRED)
#   INCLUDE_DIRECTORIES(${LIBUSB_1_INCLUDE_DIRS})
#   SET(LIBTRANCEVIBE_DEP_LIBS ${LIBUSB_1_LIBRARIES})
# ELSE()
  FIND_PACKAGE(libusb REQUIRED)
  INCLUDE_DIRECTORIES(${LIBUSB_INCLUDE_DIRS})
  SET(LIBTRANCEVIBE_DEP_LIBS ${LIBUSB_LIBRARIES})
# ENDIF()                         

######################################################################################
# Project specific globals
######################################################################################

#library definitions

SET(LIBTRANCEVIBE_MAJOR_VERSION 0)
SET(LIBTRANCEVIBE_MINOR_VERSION 5)
SET(LIBTRANCEVIBE_BUILD_VERSION 0)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# BUILDSYS_CPACK_INFO(
#   NAME "libtrancevibe"
#   MAJOR_VERSION ${LIBNIFALCON_MAJOR_VERSION}
#   MINOR_VERSION ${LIBNIFALCON_MINOR_VERSION}
#   BUILD_VERSION ${LIBNIFALCON_BUILD_VERSION}
#   VENDOR "Nonpolynomial Labs"
#   DESCRIPTION "Open Source Driver for the Rez Trancevibrator and compatiable toys"
#   )
# INCLUDE(CPack)

SET(LIBTRANCEVIBE_VERSION ${LIBTRANCEVIBE_MAJOR_VERSION}.${LIBTRANCEVIBE_MINOR_VERSION}.${LIBTRANCEVIBE_BUILD_VERSION})

#library name definitions

CREATE_LIBRARY_LINK_NAME(trancevibe)

INCLUDE_DIRECTORIES(${LIBTRANCEVIBE_INCLUDE_DIR})
LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})

#If we build libusb staticly on apple, we need the proper frameworks
IF(BUILD_STATIC AND APPLE)
  LIST(APPEND LIBTRANCEVIBE_DEP_LIBS "-framework IOKit" "-framework CoreFoundation")
ENDIF(BUILD_STATIC AND APPLE)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(examples)
