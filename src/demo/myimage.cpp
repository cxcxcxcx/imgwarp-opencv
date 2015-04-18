#include "myimage.h"
#include <QColor>

MyImage::MyImage() : QImage() {
    pt = NULL;
    u1 = NULL;
    u2 = NULL;
    u3 = NULL;
}

MyImage::MyImage(const QString &fileName, const char *format)
    : QImage(fileName, format) {
    pt = NULL;
    u1 = NULL;
    u2 = NULL;
    u3 = NULL;
}
MyImage::MyImage(const char *fileName, const char *format)
    : QImage(fileName, format) {
    pt = NULL;
    u1 = NULL;
    u2 = NULL;
    u3 = NULL;
}
MyImage::MyImage(const QImage &image) : QImage(image) {
    pt = NULL;
    u1 = NULL;
    u2 = NULL;
    u3 = NULL;
}
/*
MyImage::MyImage ( const MyImage & image ):QImage(image){
    pt=NULL;u1=NULL;u2=NULL;u3=NULL;
}*/
MyImage::MyImage(uchar *data,int width,int height,Format format):QImage(data,width,height,format){
}
void MyImage::setPixelRGB(int x, int y, float r, float g, float b) {
    if (r < 0) r = 0;
    if (g < 0) g = 0;
    if (b < 0) b = 0;
    if (r > 255) r = 255;
    if (g > 255) g = 255;
    if (b > 255) b = 255;
    QRgb value = qRgb((int)r, (int)g, (int)b);
    setPixel(x, y, value);
}
void MyImage::setPixelYUV(int x, int y, float Y, float u, float v) {
    if (Y < 0) Y = 0;
    if (Y > 255) Y = 255;
    if (u < -111.18) u = -111.18;
    if (u > 111.18) u = 111.18;
    if (v < -156.825) v = -156.825;
    if (v > 156.825) v = 156.825;
    float r = Y + 1.14 * v;
    float g = Y - 0.395 * u - 0.581 * v;
    float b = Y + 2.032 * u;
    setPixelRGB(x, y, r, g, b);
}
void MyImage::RGB2YUV(float r, float g, float b, float &y, float &u, float &v) {
    y = 0.299 * r + 0.587 * g + 0.114 * b;
    u = 0.492 * (b - y);
    v = 0.877 * (r - y);
    return;
}
void MyImage::YUV2RGB(float y, float u, float v, float &r, float &g, float &b) {
    r = y + 1.14 * v;
    g = y - 0.395 * u - 0.581 * v;
    b = y + 2.032 * u;
    return;
}
void MyImage::init() {
    pt = bits();
    QSize isize = size();
    int TotalBits = isize.width() * isize.height();
    u1 = new uchar[TotalBits];
    u2 = new uchar[TotalBits];
    u3 = new uchar[TotalBits];
    int i;
    for (i = 0; i < TotalBits * 4; i++) {
        if (i % 4 == 0) {
            u1[i / 4] = pt[i];
        } else if (i % 4 == 1) {
            u2[i / 4] = pt[i];
        } else if (i % 4 == 2) {
            u3[i / 4] = pt[i];
        } else {
            ;
        }
    }
}

// Convert IplImage to QImage
MyImage MyImage::fromIplImage(const IplImage * iplImage,double mini, double maxi){
    uchar *qImageBuffer = NULL;
    int width = iplImage->width;

/* Note here that OpenCV image is stored so that each lined is
32-bits aligned thus
* explaining the necessity to "skip" the few last bytes of each
line of OpenCV image buffer.
*/
    int widthStep = iplImage->widthStep;
    int height = iplImage->height;

    switch (iplImage->depth)
    {
        case IPL_DEPTH_8U:
            if(iplImage->nChannels == 1)
            {
            /* OpenCV image is stored with one byte grey pixel. We convert it
            to an 8 bit depth QImage.
            */
                qImageBuffer = (uchar *) malloc(width*height*4*sizeof(uchar));
                uchar *QImagePtr = qImageBuffer;
                const uchar *iplImagePtr = (const uchar *) iplImage->imageData;
                for(int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        // We cannot help but copy manually.
                        QImagePtr[0] = iplImagePtr[0];
                        QImagePtr[1] = iplImagePtr[0];
                        QImagePtr[2] = iplImagePtr[0];
                        QImagePtr[3] = 0;

                        QImagePtr += 4;
                        iplImagePtr ++;
                    }
                    iplImagePtr += widthStep-width;
                }
            }
            else if(iplImage->nChannels == 3)
            {
                /* OpenCV image is stored with 3 byte color pixels (3 channels).
                    We convert it to a 32 bit depth QImage.
                */
                qImageBuffer = (uchar *) malloc(width*height*4*sizeof(uchar));
                uchar *QImagePtr = qImageBuffer;
                const uchar *iplImagePtr = (const uchar *) iplImage->imageData;
                for(int y = 0; y < height; y++) {
                    for (int x = 0; x < width; x++) {
                        // We cannot help but copy manually.
                        QImagePtr[0] = iplImagePtr[0];
                        QImagePtr[1] = iplImagePtr[1];
                        QImagePtr[2] = iplImagePtr[2];
                        QImagePtr[3] = 0;

                        QImagePtr += 4;
                        iplImagePtr += 3;
                    }
                    iplImagePtr += widthStep-3*width;
                }
            }
            else{
                    qDebug("IplImageToQImage: image format is not supported : depth=8U and %d channels ", iplImage->nChannels);
            }
            break;
        case IPL_DEPTH_16U:
            if(iplImage->nChannels == 1)
            {
            /* OpenCV image is stored with 2 bytes grey pixel. We convert it
            to an 8 bit depth QImage.
            */
                qImageBuffer = (uchar *) malloc(width*height*sizeof(uchar));
                uchar *QImagePtr = qImageBuffer;
                    //const uint16_t *iplImagePtr = (const uint16_t *);
                const unsigned int *iplImagePtr = (const unsigned int *)iplImage->imageData;
                for (int y = 0; y < height; y++){
                    for (int x = 0; x < width; x++){
                        // We take only the highest part of the 16 bit value. It is
                        //similar to dividing by 256.
                            *QImagePtr++ = ((*iplImagePtr++) >> 8);
                    }
                    iplImagePtr += widthStep/sizeof(unsigned int)-width;
                }
            }
            else{
                qDebug("IplImageToQImage: image format is not supported : depth=16U and %d channels ", iplImage->nChannels);
            }
            break;
        case IPL_DEPTH_32F:
             if(iplImage->nChannels == 1)
             {
             /* OpenCV image is stored with float (4 bytes) grey pixel. We
            convert it to an 8 bit depth QImage.
            */
                 qImageBuffer = (uchar *)malloc(width * height * sizeof(uchar));
                 uchar *QImagePtr = qImageBuffer;
                 const float *iplImagePtr = (const float *)iplImage->imageData;
                 for (int y = 0; y < height; y++) {
                     for (int x = 0; x < width; x++) {
                         uchar p;
                         float pf =
                             255 * ((*iplImagePtr++) - mini) / (maxi - mini);
                         if (pf < 0)
                             p = 0;
                         else if (pf > 255)
                             p = 255;
                         else
                             p = (uchar)pf;

                         *QImagePtr++ = p;
                     }
                     iplImagePtr += widthStep / sizeof(float) - width;
                 }
             } else {
                     qDebug("IplImageToQImage: image format is not supported : depth=32F and %d channels ", iplImage->nChannels);
             }
             break;
        case IPL_DEPTH_64F:
             if(iplImage->nChannels == 1){
                /* OpenCV image is stored with double (8 bytes) grey pixel. We
                convert it to an 8 bit depth QImage.
                */
                qImageBuffer = (uchar *) malloc(width*height*sizeof(uchar));
                uchar *QImagePtr = qImageBuffer;
                const double *iplImagePtr = (const double *) iplImage->imageData;
                for(int y = 0; y < height; y++){
                    for(int x = 0; x < width; x++){
                        uchar p;
                        double pf = 255 * ((*iplImagePtr++) - mini) / (maxi - mini);

                        if(pf < 0) p = 0;
                        else if(pf > 255) p = 255;
                        else p = (uchar) pf;

                        *QImagePtr++ = p;
                    }
                    iplImagePtr += widthStep/sizeof(double)-width;
                }
            }
            else{
                qDebug("IplImageToQImage: image format is not supported : depth=64F and %d channels ", iplImage->nChannels);
            }
            break;
        default:
                qDebug("IplImageToQImage: image format is not supported : depth=%d and %d channels ", iplImage->depth, iplImage->nChannels);
    }


    MyImage qImage;
    QVector<QRgb> vcolorTable;
    /*
    if(iplImage->nChannels == 1)
    {
        // We should check who is going to destroy this allocation.
        for(int i = 0; i < 256; i++)
        {
            vcolorTable.push_back( qRgb(i, i, i) );
        }
        qImage = MyImage(qImageBuffer, width, height, QImage::Format_Indexed8).copy();
        qImage.setColorTable(vcolorTable);
    }
    else
    {*/
        qImage = MyImage(qImageBuffer, width, height, QImage::Format_RGB32).copy();
    //}
    free(qImageBuffer);
    return qImage;
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

IplImage *MyImage::toIplImage() const {
    int width = this->width();
    int height = this->height();

    CvSize Size;
    Size.height = height;
    Size.width = width;

    IplImage *charIplImageBuffer = cvCreateImage(Size, IPL_DEPTH_8U, 1);
    char *charTemp = (char *)charIplImageBuffer->imageData;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            charTemp[index] = (char)qGray(this->pixel(x, y));
        }
    }

    return charIplImageBuffer;
}

MyImage MyImage::fromMat(const Mat &m, double mini, double maxi) {
    const IplImage mImg(m);
    return fromIplImage(&mImg, mini, maxi);
}

vector<cv::Point2i> getVcvPoint(const QList<QPoint> &qL) {
    vector<cv::Point2i> vL;
    foreach (QPoint qp, qL) { vL.push_back(cv::Point2i(qp.x(), qp.y())); }
    return vL;
}
