/*
 *  delaunay.h
 *  aamlib-opencv
 *
 *  Created by Chen Xing on 10-2-12.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "opencv2/opencv.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>
using cv::Point_;
using std::vector;

struct Triangle {
    Point_<int> v[3];
};

template <class T>
vector<Triangle> delaunayDiv(const vector<Point_<T> > &vP, cv::Rect boundRect) {
    cv::Subdiv2D subdiv(boundRect);
    for (size_t e = 0; e < vP.size(); e++) {
        subdiv.insert(vP[e]);
    }
    std::vector<cv::Vec6f> triangleList;
    subdiv.getTriangleList(triangleList);
    std::vector<Triangle> output;
    for (size_t i = 0; i < triangleList.size(); ++i) {
        Triangle triangle;
        for (int j = 0; j < 3; ++j) {
            triangle.v[j] = cv::Point(triangleList[i][j * 2], triangleList[i][j * 2 + 1]);
        }
        output.push_back(triangle);
    }
    return output;
}

