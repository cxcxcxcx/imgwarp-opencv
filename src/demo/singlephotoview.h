#ifndef SINGLEPHOTOVIEW_H
#define SINGLEPHOTOVIEW_H

#include <QGraphicsView>
#include "pointspaint.h"

class SinglePhotoView : public QGraphicsView
{
Q_OBJECT
public:
    explicit SinglePhotoView(QWidget *parent = 0);
    ~SinglePhotoView();

    void zoomIn();
    void zoomOut();
    void setImage(const QString & imgFileName);
    void setImage(const QPixmap & img);
    void setPointList(
            const QList< QPoint > &qlSrc,
            const QList< QPoint > &qlDst);
    void copySrcPointsToDst();
    void clearAllPoints();
    PointsPaint srcPointPaint, dstPointPaint;
signals:
    void pointsUpdated();

public slots:

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    QGraphicsScene gScene;

    // QList< QPoint > selectedPoints;

    double scaleFactor;

private:
    bool dragging;
    PointsPaint *pppCur, *pppOther;

    QString imageFileName;

    QGraphicsPixmapItem *pixItem;
    QPixmap pixData;
};

#endif // SINGLEPHOTOVIEW_H
