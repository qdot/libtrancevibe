######################################################################################
# CMake directives
######################################################################################

#Require 2.6 or higher. 
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0 FATAL_ERROR)

#See if we've got our cmake modules checked out. If not, advise to do so.
IF(EXISTS "${CMAKE_SOURCE_DIR}/../compily_buildd/cmake")
  SET(BUILDSYS_CMAKE_DIR "${CMAKE_SOURCE_DIR}/../compily_buildd/cmake")
  MESSAGE(STATUS "Using outside compily_buildd directory ${BUILDSYS_CMAKE_DIR}")
ELSEIF(EXISTS "${CMAKE_SOURCE_DIR}/compily_buildd/cmake")
  SET(BUILDSYS_CMAKE_DIR "${CMAKE_SOURCE_DIR}/compily_buildd/cmake")
  MESSAGE(STATUS "Using compily_buildd git submodule ${BUILDSYS_CMAKE_DIR}")
ELSE(EXISTS "${CMAKE_SOURCE_DIR}/compily_buildd/cmake")
  MESSAGE(FATAL_ERROR 
    "Cannot find compily_buildd directory for np labs project compilation functions.\n"
    "Make sure you've either put the compily_buildd directory in the same root as your repository directory, or that you've used the compily_buildd submodule (git submodule update --init).\n"
    "NP Labs build repository is available at git://github.com/qdot/compily_buildd.git"
    )
ENDIF(EXISTS "${CMAKE_SOURCE_DIR}/../compily_buildd/cmake")

LIST(APPEND CMAKE_MODULE_PATH ${BUILDSYS_CMAKE_DIR})

INCLUDE( ${BUILDSYS_CMAKE_DIR}/BuildSysCMakeLib.cmake )

#setting link directory policy

IF(COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)

######################################################################################
# Project declaration and options
######################################################################################

#Project declaration

PROJECT(LIBTRANCEVIBE)
INITIALIZE_BUILD()

#Common Options

OPTION_LIBRARY_BUILD_STATIC(ON)
OPTION_LIBRARY_BUILD_SHARED(ON)

#Project specific options
OPTION(BUILD_EXAMPLES "Build libtrancevibe examples" ON)

######################################################################################
# Project specific package finding
######################################################################################

FIND_PACKAGE(libusb-1.0 REQUIRED)
INCLUDE_DIRECTORIES(${LIBUSB_1_INCLUDE_DIRS})
SET(LIBTRANCEVIBE_DEP_LIBS ${LIBUSB_1_LIBRARIES})

######################################################################################
# Project specific globals
######################################################################################

#library definitions

SET(LIBTRANCEVIBE_MAJOR_VERSION 1)
SET(LIBTRANCEVIBE_MINOR_VERSION 0)
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
