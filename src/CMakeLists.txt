######################################################################################
# Build function for main library
######################################################################################

IF(NOT WIN32)
  SET(SRCS trancevibe_libusb1.c nputil_libusb1.c)
ELSE()
  SET(SRCS trancevibe_libusb.c)
ENDIF()

BUILDSYS_BUILD_LIB(
  NAME trancevibe
  SOURCES "${SRCS}" 
  CXX_FLAGS FALSE
  LINK_LIBS ${LIBTRANCEVIBE_DEP_LIBS}
  LINK_FLAGS FALSE
  DEPENDS FALSE
  SHOULD_INSTALL TRUE
  VERSION "${LIBTRANCEVIBE_VERSION}"
  )
