#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <QImage>
#include <vector>
#include <cv.h>
using cv::Mat;
using cv::vector;

class MyImage : public QImage
{
public:
    MyImage();
    MyImage ( const QString & fileName, const char * format = 0 );
    MyImage ( const char * fileName, const char * format = 0 );
    MyImage ( const QImage & image );
    MyImage(uchar *data,int width,int height,Format format);
    void setPixelRGB(int x,int y,float r,float g,float b);
    void setPixelYUV(int x,int y,float Y,float u,float v);
    static void YUV2RGB(float y,float u,float v,float &r,float &g,float &b);
    static void RGB2YUV(float r,float g,float b,float &y,float &u,float &v);


    IplImage * toIplImage() const;

    static MyImage fromIplImage(const IplImage * iplImage,double mini=0, double maxi=0);

	//! Convert from OpenCV 2.x Mat
    static MyImage fromMat(const Mat &m, double mini=0, double maxi=0);

    static MyImage fusionTwoImages(const MyImage & img1, const MyImage &img2, double r);

private:
    uchar *pt;
    uchar *u1,*u2,*u3;

    void init();
};

//! QList< QPoint > to cvPoint list
vector<cv::Point2i> getVcvPoint(const QList< QPoint > &qL);
#endif // MYIMAGE_H
