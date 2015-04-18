#include "singlephotoview.h"
#include <QMouseEvent>

SinglePhotoView::SinglePhotoView(QWidget *parent) :
    QGraphicsView(parent)
{
    setScene(&gScene);
    scaleFactor = 1;
    pixItem = NULL;
    dragging = false;

    // this->scale(scaleFactor, scaleFactor);
    this->setRenderHint(QPainter::Antialiasing);
    this->setRenderHint(QPainter::SmoothPixmapTransform);

    srcPointPaint.setColorScheme(0);
    dstPointPaint.setColorScheme(1);
    gScene.addItem(&srcPointPaint);
    gScene.addItem(&dstPointPaint);
    srcPointPaint.setRatio(this->mapToScene(1, 0).x()-this->mapToScene(0, 0).x());
    dstPointPaint.setRatio(this->mapToScene(1, 0).x()-this->mapToScene(0, 0).x());
}

SinglePhotoView::~SinglePhotoView()
{
    gScene.removeItem(&srcPointPaint);
    gScene.removeItem(&dstPointPaint);
}

void SinglePhotoView::zoomIn(){
    scaleFactor *= 1.2;
    this->scale(1.2, 1.2);
    this->setRenderHint(QPainter::SmoothPixmapTransform);
    srcPointPaint.setRatio(this->mapToScene(1, 0).x()-this->mapToScene(0, 0).x());
    dstPointPaint.setRatio(this->mapToScene(1, 0).x()-this->mapToScene(0, 0).x());
    this->update();
}

void SinglePhotoView::zoomOut(){
    scaleFactor /= 1.2;
    this->scale(1/1.2, 1/1.2);
    srcPointPaint.setRatio(this->mapToScene(1, 0).x()-this->mapToScene(0, 0).x());
    dstPointPaint.setRatio(this->mapToScene(1, 0).x()-this->mapToScene(0, 0).x());
    this->update();
}

void SinglePhotoView::mousePressEvent(QMouseEvent *event){
    QPointF qp = this->mapToScene(event->x(),event->y());

    if (event->button()==Qt::LeftButton)
        pppCur = &dstPointPaint, pppOther = &srcPointPaint;
    else
        pppCur = &srcPointPaint, pppOther = &dstPointPaint;

	// Shift+Click: Remove the last point
	if (event->modifiers() & Qt::ShiftModifier){
		pppCur->rmLastPoint();
        pppCur->selectPoint(-1);
        pppOther->setMirrorPoint(-1);
        emit pointsUpdated();
	}

    int tI = pppCur->pickPointByMouse(qp);
    if (tI != -1){
        pppCur->selectPoint(tI);
        pppOther->setMirrorPoint(tI);
        dragging = true;
    }
    // Ctrl+Click: Add a point
    else if (event->modifiers() & Qt::ControlModifier) {
        pppCur->addPoint(qp);
        pppCur->selectPoint(-1);
        pppOther->setMirrorPoint(pppCur->getSize());
        emit pointsUpdated();
    }
}

void SinglePhotoView::setImage(const QString & imgFileName)
{
    setImage(QPixmap(imgFileName));
}

void SinglePhotoView::setImage(const QPixmap &img)
{
    if (pixItem != NULL){
        gScene.removeItem(pixItem);
        delete pixItem;
    }

    pixData = img;
    pixItem = gScene.addPixmap(pixData);
    pixItem->setTransformationMode(Qt::SmoothTransformation);

    this->setSceneRect(QRect(QPoint(0, 0), pixData.size()));
    gScene.setSceneRect(QRect(QPoint(0, 0), pixData.size()));
    this->update();
}

void SinglePhotoView::mouseReleaseEvent(QMouseEvent *event)
{
    dragging = false;
}

void SinglePhotoView::mouseMoveEvent(QMouseEvent *event)
{
    if ( dragging ){
        pppCur->updateSelectedPoint(this->mapToScene(event->pos()));
        emit pointsUpdated();
        return;
    }
    QPointF qp = this->mapToScene(event->x(),event->y());
    int tI;
    tI = srcPointPaint.pickPointByMouse(qp);
    srcPointPaint.highLight(tI);
    tI = dstPointPaint.pickPointByMouse(qp);
    dstPointPaint.highLight(tI);
    QGraphicsView::mouseMoveEvent(event);
}

void SinglePhotoView::setPointList(
        const QList< QPoint > &qlSrc,
        const QList< QPoint > &qlDst){
    srcPointPaint.clear();
    dstPointPaint.clear();
    int i;
    for (i=0;i<qlSrc.size();i++)
        srcPointPaint.addPoint(QPointF(qlSrc[i]));
    for (i=0;i<qlDst.size();i++)
        dstPointPaint.addPoint(QPointF(qlDst[i]));
    emit pointsUpdated();
}

void SinglePhotoView::copySrcPointsToDst()
{
    dstPointPaint.clear();
    QList< QPoint > qtemp = srcPointPaint.getPointList();
    for (int i=0;i<qtemp.size();i++)
        dstPointPaint.addPoint(QPointF(qtemp[i]));
    emit pointsUpdated();
    this->update();
}

void SinglePhotoView::clearAllPoints()
{
    dstPointPaint.clear();
    srcPointPaint.clear();
    emit pointsUpdated();
    this->update();
}

#include "singlephotoview.moc"
