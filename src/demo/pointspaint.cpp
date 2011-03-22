#include "pointspaint.h"
#include <QPainter>

PointsPaint::PointsPaint()
{
    mouseHighlightPoint = -1;
    selectedPoint = -1;
    boundRect.setCoords(0, 0, 0, 0);
    setZValue(1);
    setColorScheme(0);
}

void PointsPaint::setColorScheme(int schemeId)
{
    if (schemeId == 0){
        colorBrush = Qt::magenta;
        colorSelectedPen = Qt::yellow;
        colorSelectedBrush = Qt::darkYellow;
        colorHighlightPen = Qt::blue;
        colorMirrorPen = Qt::darkRed;
        colorMirrorBrush = Qt::red;
        colorPen = Qt::black;
    }
    else {
        colorBrush = Qt::gray;
        colorSelectedPen = Qt::green;
        colorSelectedBrush = Qt::darkGreen;
        colorHighlightPen = Qt::red;
        colorMirrorPen = Qt::darkRed;
        colorMirrorBrush = Qt::red;
        colorPen = Qt::darkBlue;
    }
}

QRectF PointsPaint::boundingRect() const{
    /*
    QList< QPoint >::iterator ci;
    for (ci = ql->begin(); ci != ql->end(); ci++){
        if ( ci->x() > boundRect.right() )
            boundRect.setRight(ci->x());
        if ( ci->x() < boundRect.left() )
            boundRect.setLeft(ci->x());
        if ( ci->y() > boundRect.bottom() )
            boundRect.setBottom(ci->y());
        if ( ci->y() < boundRect.top() )
            boundRect.setTop(ci->y());
    }
    qDebug("%d",boundRect.top());//<<" "<<boundingRect.top()<<endl;*/
    return (QRectF)boundRect;
}

void PointsPaint::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
    QWidget *){
    int i;
    QPen dPen;
    QBrush dBrush;
    dBrush.setStyle(Qt::SolidPattern);
    dBrush.setColor(colorBrush);
    painter->setBrush(dBrush);

    //double ratio = this->(1,0).x()-this->mapFromScene(0, 0).x();
    //qDebug("%lf\n",ratio);

    for (i = 0; i < ql.size(); i++){
        if (selectedPoint == i){
            dPen.setColor(colorSelectedPen);
            painter->setPen(dPen);
            dBrush.setColor(colorSelectedBrush);
            painter->setBrush(dBrush);
            painter->drawEllipse(QPointF(ql[i]), 4.*ratio, 4.*ratio);
            dBrush.setColor(colorBrush);
            painter->setBrush(dBrush);
        }
        else if (mouseHighlightPoint == i){
            dPen.setColor(colorHighlightPen);
            painter->setPen(dPen);
            painter->drawEllipse(QPointF(ql[i]), 4.*ratio, 4.*ratio);
        }
        else if (mirrorPoint == i){
            dPen.setColor(colorMirrorPen);
            painter->setPen(dPen);
            dBrush.setColor(colorMirrorBrush);
            painter->setBrush(dBrush);
            painter->drawEllipse(QPointF(ql[i]), 4.*ratio, 4.*ratio);
            dBrush.setColor(colorBrush);
            painter->setBrush(dBrush);
        }
        else {
            dPen.setColor(colorPen);
            painter->setPen(dPen);
            painter->drawEllipse(QPointF(ql[i]), 3.*ratio, 3.*ratio);
        }
    }
}

// Pick a point by mouse. mouseP is in item coordination system.
int PointsPaint::pickPointByMouse(const QPointF &mouseP) const{
    double minD=1e10, dist;
    int i, minI;

    for (i = 0; i < ql.size(); i++){
        dist = (mouseP.x() - ql[i].x())*(mouseP.x() - ql[i].x()) +
               (mouseP.y() - ql[i].y())*(mouseP.y() - ql[i].y());
        if ( dist<minD ) {
            minD = dist;
            minI = i;
        }
    }
    if (minD < 16*ratio*ratio)
        return minI;
    else
        return -1;
}

void PointsPaint::highLight(int pId){
    if (mouseHighlightPoint != pId){
        mouseHighlightPoint = pId;
        this->update();
    }
}

void PointsPaint::selectPoint(int pId){
    if (selectedPoint!=pId){
        selectedPoint = pId;
        mirrorPoint = -1;
        this->update();
    }
}


void PointsPaint::setMirrorPoint(int pId){
    if (mirrorPoint != pId){
        mirrorPoint = pId;
        selectedPoint = -1;
        this->update();
    }
}

void PointsPaint::updateSelectedPoint(const QPointF &mouseP){
    QPoint qp = mouseP.toPoint();
    if (qp.x() != ql[selectedPoint].x() || qp.y() != ql[selectedPoint].y()){
        ql[selectedPoint] = qp;
        testUpdateRect(qp);
    }
    this->update();
}

// Pick a point by mouse. mouseP is in item coordination system.
void PointsPaint::addPoint(const QPointF &mouseP) {
    ql.append(mouseP.toPoint());
    testUpdateRect(mouseP.toPoint());
    this->update();
}

void PointsPaint::testUpdateRect(const QPoint &qp){
    bool needUpdate = false;
    if (qp.y()+3>boundRect.bottom())
        boundRect.setBottom(qp.y()+3), needUpdate=true;
    if (qp.x()+3>boundRect.right())
        boundRect.setRight(qp.x()+3), needUpdate=true;
    if (needUpdate)
        this->prepareGeometryChange();
}

void PointsPaint::clear()
{
    ql.clear();
    mouseHighlightPoint = -1;
    selectedPoint = -1;
    boundRect.setCoords(0, 0, 0, 0);
    setZValue(1);
}

#include "pointspaint.moc"