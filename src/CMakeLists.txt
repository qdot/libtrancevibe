######################################################################################
# Build function for main library
######################################################################################

INCLUDE_DIRECTORIES(../libnputil/src)

SET(SRCS trancevibe_libusb1.c)

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
