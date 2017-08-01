#ifndef MASTERJPEG_HPP
#define MASTERJPEG_HPP

#include <QObject>
#include <QImage>
#include "jpeglib.h"

class MainWindow;

class MasterJPEG : public QObject
{
	Q_OBJECT

private:
	std::vector<unsigned char*> lines;
	QMetaObject::Connection handleImageLoad;
	uint64_t imageWidth;
	uint64_t imageHeight;
	void setPictureWidth(const JDIMENSION width);
	void setPictureHeight(const JDIMENSION height);
	void storeScannedLine(JSAMPROW sampledLine);
	void buildMasterImage();
	QImage *masterImage;

public:
	explicit MasterJPEG(const QString& jpegName, MainWindow *mainWindow);
	~MasterJPEG();
	QImage* getMasterImage();

signals:
	void showImage(QImage*,int,int,int,int);


public slots:

};

#endif // MASTERJPEG_HPP
