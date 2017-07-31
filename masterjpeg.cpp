#include <vector>
#include <QString>
#include <QImage>
#include "jpeglib.h"
#include "masterjpeg.hpp"
#include "mainwindow.h"

using namespace std;


MasterJPEG::MasterJPEG(const QString& jpegName, MainWindow *mainWindow)
{
	handleImageLoad = QObject::connect(this, SIGNAL(imageLoaded()),
		this, SLOT(showLoadedImage()));
	handleImageDisplay = QObject::connect(this,
		SIGNAL(drawImage(QImage*,const uint64_t,const uint64_t,const uint64_t,const uint64_t)),
		mainWindow,
		SLOT(showImage(QImage*,const uint64_t,const uint64_t,const uint64_t, const uint64_t)));
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE* inFile;
	JSAMPARRAY buffer;
	int row_stride;

	if ((inFile = fopen(qPrintable(jpegName), "rb")) == NULL){
		fprintf(stderr, "cannot open %s\n", qPrintable(jpegName));
		return;
	}

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, inFile);
	jpeg_read_header(&cinfo, TRUE);
	cinfo.out_color_space = JCS_GRAYSCALE;
	jpeg_start_decompress(&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;
	setPictureWidth(cinfo.image_width);
	setPictureHeight(cinfo.image_height);

	buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr)
		&cinfo, JPOOL_IMAGE, row_stride, 1);

	while (cinfo.output_scanline < cinfo.output_height) {
		jpeg_read_scanlines(&cinfo, buffer, 1);
		storeScannedLine(buffer[0]);
	}
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(inFile);

	emit imageLoaded();
}

MasterJPEG::~MasterJPEG()
{
	QObject::disconnect(handleImageLoad);
	QObject::disconnect(handleImageDisplay);
	delete mainPicture;
}

void MasterJPEG::setPictureWidth(const JDIMENSION width)
{
	imageWidth = width;
}

void MasterJPEG::setPictureHeight(const JDIMENSION height)
{
	imageHeight = height;
}

void MasterJPEG::storeScannedLine(JSAMPROW sampledLine)
{
	unsigned char* lineIn = (unsigned char *)malloc(imageWidth);
	memcpy(lineIn, sampledLine, imageWidth);
	lines.push_back(lineIn);
}

void MasterJPEG::_showLoadedImage(const uint64_t topXImage,
	const uint64_t topYImage,const uint64_t topXframe,
	const uint64_t topYFrame)
{
	emit drawImage(mainPicture, topXframe, topYImage, topXframe,
		topYFrame);
}


void MasterJPEG::showLoadedImage()
{
	mainPicture = new QImage(imageWidth, imageHeight,
		QImage::Format_Grayscale8);
	int i = 0;
	for (auto innerLine: lines){
		for (uint j = 0; j < imageWidth; j++)
		{
			uint8_t value = *(innerLine + j);
			QRgb pixels = qRgb(value, value, value);
			mainPicture->setPixel(j, i, pixels);
		}
		i++;
	}

	_showLoadedImage(0, 0, 0, 0);
}



