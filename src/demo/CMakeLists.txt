project(demo)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
FIND_PACKAGE( OpenCV REQUIRED )


include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR}/lib ${CMAKE_CURRENT_SOURCE_DIR})

set(demo_SRCS main.cpp projfile.cpp deformwin.cpp myimage.cpp singlephotoview.cpp pointspaint.cpp)
qt4_automoc(${demo_SRCS})
QT4_WRAP_CPP(QOBJ_CPP ${demo_SRCS})
qt4_wrap_ui(helloworld_FORMS_HEADERS deformwin.ui)
add_executable(demo ${demo_SRCS} ${helloworld_FORMS_HEADERS})
target_link_libraries(demo ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} imgwarp-lib ${OpenCV_LIBS})
