#ifndef DEFORMWIN_H
#define DEFORMWIN_H

#include <QMainWindow>

#include<QGraphicsScene>

#include "imgwarp_mls.h"
#include "myimage.h"
#include "projfile.h"

namespace Ui {
    class DeformWin;
}

class DeformWin : public QMainWindow {
    Q_OBJECT
public:
    DeformWin(QWidget *parent = 0);
    ~DeformWin();

    void prepare();

    QList< QPoint > qDotSrc, qDotDst;
    QString srcFile;

public slots:
    void updateEditImg();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::DeformWin *ui;

    ProjFile pFile;

    QGraphicsScene *scene;
    
    //! The original image
    Mat oriImg;
    
    //! The current warped image
    Mat curImg;
    
    //! Get the warped image
    bool calcWarpedImg();

private slots:
    void on_actExportPic_triggered();
    void on_actSaveProjAs_triggered();
    void on_actSaveProj_triggered();
    void on_actOpenProj_triggered();
    void on_actNewProj_triggered();
    void on_actClearAllPt_triggered();
    void on_actCpSrcPtToDst_triggered();
    void on_actExit_triggered();
    void on_pushButton_clicked();
};

#endif // DEFORMWIN_H
