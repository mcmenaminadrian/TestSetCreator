#include <QString>
#include <QFileDialog>
#include <fstream>
#include "jpeglib.h"
#include "masterjpeg.hpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	FILE* inFile;
	ui->setupUi(this);

	jpegFile = QFileDialog::getOpenFileName(this, tr("Pick JPEG"), "");
	if ((inFile = fopen(qPrintable(jpegFile), "rb")) == NULL){
			fprintf(stderr, "cannot open %s\n", qPrintable(jpegFile));
			return;
	}
	//load the file
	displayScene = new QGraphicsScene();
	ui->graphicsView->setScene(displayScene);
	MasterJPEG bigJPEG(jpegFile, this);
}

MainWindow::~MainWindow()
{
	delete displayScene;
	delete ui;
}

void MainWindow::showImage(QImage *picture, const uint64_t xImage,
	const uint64_t yImage, const uint64_t xFrame, const uint64_t yFrame)
{
	QPixmap bigPicture = QPixmap::fromImage(*picture);
	bigPicture.scroll(xImage, yImage, bigPicture.rect());
	displayScene->addPixmap(bigPicture);
}
