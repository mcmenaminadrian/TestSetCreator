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
	QImage* masterImage;
	void setPictureWidth(const JDIMENSION width);
	void setPictureHeight(const JDIMENSION height);
	void storeScannedLine(JSAMPROW sampledLine);
	void buildMasterImage();

public:
	explicit MasterJPEG(const QString& jpegName, MainWindow *mainWindow);
	~MasterJPEG();
	QImage* getMasterImage() const;

signals:
	void imageBuilt();


public slots:

};

#endif // MASTERJPEG_HPP
