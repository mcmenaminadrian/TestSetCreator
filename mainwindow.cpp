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

	jpegFile = QFileDialog::getOpenFileName(this, tr("Pick JPEG"), "",
		tr("JPEGs (*.jpeg *.jpg *.jfif)"));
	if ((inFile = fopen(qPrintable(jpegFile), "rb")) == NULL){
			fprintf(stderr, "cannot open %s\n", qPrintable(jpegFile));
			return;
	}
	//load the file
	displayScene = new QGraphicsScene();
	ui->graphicsView->setScene(displayScene);
	QObject::connect(this, SIGNAL(showImage(QImage*,const int,const int,const int,const int)),
		ui->graphicsView,
		SLOT(displayImage(QImage*, const int, const int, const int, const int)));
	bigJPEG = new MasterJPEG(jpegFile, this);
	displayInitialImage();
}

MainWindow::~MainWindow()
{
	delete bigJPEG;
	delete displayScene;
	delete ui;
}


void MainWindow::displayInitialImage()
{
	QImage *initialImage = bigJPEG->getMasterImage();
	emit showImage(initialImage, 0, 0, 0, 0);
}
