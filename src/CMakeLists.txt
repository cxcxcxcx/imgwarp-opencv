PROJECT( imgwarp-opencv )
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
FIND_PACKAGE( OpenCV REQUIRED )

SET(IMGWARP_SRC delaunay.cpp imgwarp_mls_similarity.cpp imgwarp_mls.cpp imgwarp_mls_rigid.cpp imgwarp_piecewiseaffine.cpp)
#SET(TEST_SRC main.cpp)

INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )
#ADD_EXECUTABLE( test ${LIB_SRC_LIST} ${TEST_SRC} )
#TARGET_LINK_LIBRARIES( test ${OPENCV_LIBRARIES} )

ADD_LIBRARY( imgwarp-opencv STATIC ${IMGWARP_SRC} )

add_subdirectory(demo)