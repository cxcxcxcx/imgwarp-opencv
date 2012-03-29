PROJECT( imgwarp-lib )
FIND_PACKAGE( OpenCV REQUIRED )

SET(IMGWARP_SRC delaunay.cpp imgwarp_mls_similarity.cpp imgwarp_mls.cpp imgwarp_mls_rigid.cpp imgwarp_piecewiseaffine.cpp)

INCLUDE_DIRECTORIES( ${OPENCV_INCLUDE_DIR} )

ADD_LIBRARY( imgwarp-lib STATIC ${IMGWARP_SRC} )
