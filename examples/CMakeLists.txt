######################################################################################
# Build function for tvtest
######################################################################################

SET(SRCS tvtest/tvtest.c)

BUILDSYS_BUILD_EXE(
  NAME tvtest
  SOURCES "${SRCS}" 
  CXX_FLAGS FALSE
  LINK_LIBS ${libtrancevibe_LIBRARY} ${LIBTRANCEVIBE_DEP_LIBS}
  LINK_FLAGS FALSE 
  DEPENDS ${libtrancevibe_LIBRARY}_DEPEND
  SHOULD_INSTALL TRUE
  )

