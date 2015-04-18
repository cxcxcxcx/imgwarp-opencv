#include "deformwin.h"
#include "ui_deformwin.h"

#include "imgwarp_piecewiseaffine.h"
#include "imgwarp_mls_rigid.h"
#include "imgwarp_mls_similarity.h"
#include "highgui.h"

#include <QString>
#include <QFileDialog>

using cv::imread;

DeformWin::DeformWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeformWin)
{
    ui->setupUi(this);
    scene = NULL;
}

DeformWin::~DeformWin()
{
    delete ui;
}

void DeformWin::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void DeformWin::on_pushButton_clicked()
{
    ui->tabMain->setCurrentWidget(ui->tabView);
	calcWarpedImg();
    MyImage mNew = MyImage::fromMat(curImg);

    if (scene != NULL){
        delete scene;
        scene = NULL;
    }
    scene = new QGraphicsScene();

    qDebug("New Image generated.");
    scene->addPixmap(QPixmap::fromImage(mNew));
    ui->graphShow->setScene(scene);
    ui->graphShow->fitInView(0, 0, oriImg.cols, oriImg.rows,
							 Qt::KeepAspectRatio);
}

void DeformWin::updateEditImg()
{
	if (oriImg.cols == 0)
		return;
    // Check if preview is available
    if (ui->viewPointEdit->srcPointPaint.getPointList().length() !=
        ui->viewPointEdit->dstPointPaint.getPointList().length()){
        //ui->chkPreview->setChecked(false);
        ui->chkPreview->setEnabled(false);
    }
    else {
        ui->chkPreview->setEnabled(true);
    }
    // Check if "preview" is checked
    if (!ui->chkPreview->isChecked()){
        ui->viewPointEdit->setImage(pFile.picSrc);
        return;
    }
    calcWarpedImg();

    qDebug("New Image generated.");
    MyImage mN = MyImage::fusionTwoImages(MyImage::fromMat(oriImg),
		MyImage::fromMat(curImg), ui->SldOpacity->value()/100.0);
    ui->viewPointEdit->setImage(QPixmap::fromImage(mN));

}

bool DeformWin::calcWarpedImg(){
	if (ui->viewPointEdit->srcPointPaint.getPointList().length() !=
        ui->viewPointEdit->dstPointPaint.getPointList().length()){
		curImg = oriImg;
		return false;
	}

    ImgWarp_MLS *imgTrans;
    if (ui->cmbDeformAlg->currentText()==QString("MLS Similarity")){
        imgTrans = new ImgWarp_MLS_Similarity();
        imgTrans->alpha = ui->spinAlpha->value();
        imgTrans->gridSize = ui->SldGrid->value();
    }
    else if (ui->cmbDeformAlg->currentText()==QString("MLS Rigid")){
        imgTrans = new ImgWarp_MLS_Rigid();
        imgTrans->alpha = ui->spinAlpha->value();
        imgTrans->gridSize = ui->SldGrid->value();
    }
    else if (ui->cmbDeformAlg->currentText()==QString("Piecewise Affine")){
        imgTrans = new ImgWarp_PieceWiseAffine();
        imgTrans->alpha = ui->spinAlpha->value();
        imgTrans->gridSize = ui->SldGrid->value();
		((ImgWarp_PieceWiseAffine *)imgTrans)->backGroundFillAlg = ImgWarp_PieceWiseAffine::BGMLS;
//         imgTrans = new ImgTrans_MLS_Affine();
//         imgTrans->alpha = ui->spinAlpha->value();
//         imgTrans->gridSize = ui->SldGrid->value();
    }
    else {
//         imgTrans = new ImgTrans_MLS_Affine();
//         imgTrans->alpha = ui->spinAlpha->value();
//         imgTrans->gridSize = ui->SldGrid->value();
    }

    //imgTrans->setTargetSize(oriImg.cols, oriImg.rows);
    //imgTrans->setSize(oriImg.cols, oriImg.rows);
    //imgTrans->setSrcPoints(getVcvPoint(ui->viewPointEdit->srcPointPaint.getPointList()));
    //imgTrans->setDstPoints(getVcvPoint(ui->viewPointEdit->dstPointPaint.getPointList()));
////    imgTrans->alpha = 1;
////    imgTrans->gridSize = 10;

    //imgTrans->calcDelta();
	//curImg = imgTrans->genNewImg(oriImg, 1);
	curImg = imgTrans->setAllAndGenerate(
			oriImg,
		   	getVcvPoint(ui->viewPointEdit->srcPointPaint.getPointList()),
			getVcvPoint(ui->viewPointEdit->dstPointPaint.getPointList()),
			oriImg.cols, oriImg.rows, 1);
    delete imgTrans;
	return true;
}



void DeformWin::prepare()
{
    ui->viewPointEdit->setPointList(this->qDotSrc, qDotDst);
    ui->viewPointEdit->setImage(this->pFile.picSrc);
}

void DeformWin::on_actCpSrcPtToDst_triggered()
{
    ui->viewPointEdit->copySrcPointsToDst();
}

void DeformWin::on_actClearAllPt_triggered()
{
    ui->viewPointEdit->clearAllPoints();
}

void DeformWin::on_actNewProj_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(
        this, tr("Open Image"), "./",
        tr("Image Files (*.jpg *.gif *.png);;All Files (*.*)"));
    ui->viewPointEdit->setImage(fileName);
    ui->viewPointEdit->clearAllPoints();
    pFile.picSrc = fileName;
    this->oriImg = imread(pFile.picSrc.toStdString());
}

void DeformWin::on_actOpenProj_triggered()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(
        this, tr("Open Project"), "./",
        tr("Project Files (*.prj);;All Files (*.*)"));
        qDebug("HERE\n");
    pFile.open(fileName);

    ui->viewPointEdit->setImage(pFile.picSrc);
    this->oriImg = imread(pFile.picSrc.toStdString());
    ui->viewPointEdit->setPointList(pFile.qlSrc, pFile.qlDest);
}

void DeformWin::on_actSaveProj_triggered()
{
    if (pFile.fileName == ""){
        pFile.fileName = QFileDialog::getSaveFileName(
            this, tr("Save Project..."), "./",
            tr("Project Files (*.prj);;All Files (*.*)"));
        qDebug(pFile.fileName.toStdString().c_str());
        if (!pFile.fileName.endsWith(".prj"))
            pFile.fileName.append(".prj");
    }
    pFile.qlSrc = ui->viewPointEdit->srcPointPaint.getPointList();
    pFile.qlDest = ui->viewPointEdit->dstPointPaint.getPointList();
    pFile.save();
}

void DeformWin::on_actSaveProjAs_triggered()
{
    pFile.fileName = QFileDialog::getSaveFileName(
        this, tr("Save Project..."), "./",
        tr("Project Files (*.prj);;All Files (*.*)"));
    qDebug(pFile.fileName.toStdString().c_str());
    if (!pFile.fileName.endsWith(".prj"))
        pFile.fileName.append(".prj");
    pFile.qlSrc = ui->viewPointEdit->srcPointPaint.getPointList();
    pFile.qlDest = ui->viewPointEdit->dstPointPaint.getPointList();
    pFile.save();
}

void DeformWin::on_actExportPic_triggered()
{
	if (!calcWarpedImg()){
		// TODO: show some hint here.
		return;
	}

    QString filename;
    filename = QFileDialog::getSaveFileName(this,
        tr("Export Picture..."), "./", tr("PNG Files (*.png);;All Files (*.*)"));
    qDebug(filename.toStdString().c_str());
    if (!filename.endsWith(".png"))
        filename.append(".png");
	cv::imwrite(filename.toStdString(), curImg);
}

void DeformWin::on_actExit_triggered(){
	QApplication::exit(0);
}

#include "deformwin.moc"
