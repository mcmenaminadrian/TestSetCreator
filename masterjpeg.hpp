#ifndef MASTERJPEG_HPP
#define MASTERJPEG_HPP

#include <QObject>
#include "jpeglib.h"

class MainWindow;

class MasterJPEG : public QObject
{
	Q_OBJECT

private:
	std::vector<unsigned char*> lines;
	QMetaObject::Connection handleImageLoad;
	QMetaObject::Connection handleImageDisplay;
	uint64_t imageWidth;
	uint64_t imageHeight;
	QImage *mainPicture;
	void setPictureWidth(const JDIMENSION width);
	void setPictureHeight(const JDIMENSION height);
	void storeScannedLine(JSAMPROW sampledLine);
	void _showLoadedImage(const uint64_t xImage, const uint64_t yImage,
		const uint64_t xFrame, const uint64_t yFrame);
public:
	explicit MasterJPEG(const QString& jpegName, MainWindow *mainWindow);
	~MasterJPEG();

signals:
	void imageLoaded();
	void drawImage(QImage* picture, const uint64_t xImage,
		const uint64_t yImage, const uint64_t xFrame,
		const uint64_t yFrame);


public slots:
	void showLoadedImage();
};

#endif // MASTERJPEG_HPP
