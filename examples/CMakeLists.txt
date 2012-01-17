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

FIND_PACKAGE(Qt4)
IF(QT4_FOUND)
  include(${QT_USE_FILE})
  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
  QT4_WRAP_CPP(MOCSRCS trancevibe_qt/mainwindow.h)
  QT4_WRAP_UI(UISRCS trancevibe_qt/mainwindow.ui)
  SET(SRCS trancevibe_qt/main.cpp trancevibe_qt/mainwindow.cpp ${MOCSRCS} ${UISRCS})
  BUILDSYS_BUILD_EXE(
    NAME qt_trancevibe
    SOURCES "${SRCS}"
    CXX_FLAGS FALSE
    LINK_LIBS ${libtrancevibe_LIBRARY} ${LIBTRANCEVIBE_DEP_LIBS} ${QT_LIBRARIES}
    LINK_FLAGS FALSE
    DEPENDS ${libtrancevibe_LIBRARY}_DEPEND
    SHOULD_INSTALL TRUE
    )
ENDIF()