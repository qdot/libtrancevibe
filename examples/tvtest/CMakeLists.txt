INCLUDE_DIRECTORIES(../../src /usr/include /usr/local/include)
LINK_DIRECTORIES(../../src /usr/lib /usr/local/lib)
ADD_EXECUTABLE(tvtest tvtest.c)
TARGET_LINK_LIBRARIES(tvtest usb trancevibe)
