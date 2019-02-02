#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <QImage>
#include <vector>
#include "opencv2/opencv.hpp"
using cv::Mat;

class MyImage : public QImage
{
public:
    MyImage();
    MyImage ( const QString & fileName, const char * format = 0 );
    MyImage ( const char * fileName, const char * format = 0 );
    MyImage ( const QImage & image );
    MyImage(uchar *data,int width,int height,Format format);
    MyImage(uchar *data,int width,int height,int step, Format format)
        : QImage(data, width, height, step, format) { }

	//! Convert from OpenCV 2.x Mat
    static MyImage fromMat(const Mat &m, double mini=0, double maxi=0);

    static MyImage fusionTwoImages(const MyImage & img1, const MyImage &img2, double r);
};

//! QList< QPoint > to cvPoint list
std::vector<cv::Point2i> getVcvPoint(const QList< QPoint > &qL);
#endif // MYIMAGE_H
