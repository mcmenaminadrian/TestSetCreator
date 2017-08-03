#include <vector>
#include <QString>
#include <QImage>
#include <ctime>
#include "jpeglib.h"
#include "masterjpeg.hpp"
#include "mainwindow.h"

using namespace std;


MasterJPEG::MasterJPEG(const QString& jpegName, MainWindow *mainWindow)
{
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
	buildMasterImage();
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(inFile);

}

MasterJPEG::~MasterJPEG()
{
	delete masterImage;
	QObject::disconnect(handleImageLoad);
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

void MasterJPEG::buildMasterImage()
{
	masterImage = new QImage(imageWidth, imageHeight,
		QImage::Format_Grayscale8);
	int i = 0;
	for (auto innerLine: lines){
		for (uint j = 0; j < imageWidth; j++)
		{
			uint8_t value = *(innerLine + j);
			QRgb pixels = qRgb(value, value, value);
			masterImage->setPixel(j, i, pixels);
		}
		i++;
	}
}

QImage* MasterJPEG::getMasterImage()
{
	return masterImage;
}

void MasterJPEG::saveFragment(const QRect &fragment) const
{
	//generate title
	time_t epoch = time(nullptr);
	QString title;
	title = title.setNum(epoch, 16);
	title.prepend("JPEG_FRAG_"),
	title +=".jpeg";

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;
	FILE * outFile;
	JSAMPROW row_pointer[1];

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&cinfo);

	if ((outFile = fopen(title.toStdString().c_str(), "wb")) == NULL) {
		fprintf(stderr, "can't create %s file",
			title.toStdString().c_str());
		exit(1);
	}
	jpeg_stdio_dest(&cinfo, outFile);
	cinfo.image_width = fragment.width();
	cinfo.image_height = fragment.height();
	cinfo.input_components = 1;
	cinfo.in_color_space = JCS_GRAYSCALE;
	jpeg_set_defaults(&cinfo);

	jpeg_set_quality(&cinfo, 95, TRUE);
	jpeg_start_compress(&cinfo, TRUE);

	unsigned char* x = (unsigned char *)malloc(fragment.width());
	for (int j = 0; j < fragment.height(); j++) {
		for (int i = 0; i < fragment.width(); i++) {
			x[i] = (lines.at(fragment.top() + j))
				[fragment.left() + i];
		}
		row_pointer[0] = x;
		jpeg_write_scanlines(&cinfo, row_pointer, 1);
	}
	jpeg_finish_compress(&cinfo);
	fclose(outFile);
	jpeg_destroy_compress(&cinfo);
	free(x);
}


