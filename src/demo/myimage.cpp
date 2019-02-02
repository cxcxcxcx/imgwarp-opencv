#include "myimage.h"
#include <QColor>

using namespace std;
MyImage::MyImage() : QImage() { }

MyImage::MyImage(const QString &fileName, const char *format)
    : QImage(fileName, format) { }
MyImage::MyImage(const char *fileName, const char *format)
    : QImage(fileName, format) { }
MyImage::MyImage(const QImage &image) : QImage(image) { }

MyImage::MyImage(uchar *data,int width,int height,Format format):QImage(data,width,height,format){
}

MyImage MyImage::fusionTwoImages(const MyImage &img1, const MyImage &img2,
                                 double r) {
    QImage qi;
    qi = img1.copy();
    int i, j;
    QColor q1, q2;
    for (i = 0; i < qi.width(); i++)
        for (j = 0; j < qi.height(); j++) {
            q1 = img1.pixel(i, j);
            q2 = img2.pixel(i, j);
            qi.setPixel(i, j,
                        (QColor(q1.red() * r + q2.red() * (1 - r),
                                q1.green() * r + q2.green() * (1 - r),
                                q1.blue() * r + q2.blue() * (1 - r))).rgb());
        }
    return qi;
}

MyImage MyImage::fromMat(const Mat &mat, double mini, double maxi) {
    // TODO: process mini, maxi
    printf("%d, %d, steps: %d\n", mat.type(), mat.cols, mat.step);
    MyImage img(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    printf("%d\n", img.width());
    return img.rgbSwapped();
}

std::vector<cv::Point2i> getVcvPoint(const QList<QPoint> &qL) {
    std::vector<cv::Point2i> vL;
    foreach (QPoint qp, qL) { vL.push_back(cv::Point2i(qp.x(), qp.y())); }
    return vL;
}
