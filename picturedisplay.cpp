#include <QRect>
#include "picturedisplay.hpp"

using namespace std;

PictureDisplay::PictureDisplay(QWidget* parent):QGraphicsView(parent)
{
	xFrame = -1;
	yFrame = -1;
	QObject::connect(this, SIGNAL(signalUpdate()), this, SLOT(update()));
	displayScene = new QGraphicsScene();

}

PictureDisplay::~PictureDisplay()
{
	delete displayScene;
}

void PictureDisplay::displayImage(QImage* image, int xPic,
	int yPic, int _xFrame, int _yFrame)
{
	QPixmap bigPicture = QPixmap::fromImage(*image);
	qDeleteAll(displayScene->items());
	displayScene->addPixmap(bigPicture);
	QRect square(10, 10, 100, 100);
	displayScene->addRect(square, QPen(Qt::red));
	setScene(displayScene);
	centerOn(xPic, yPic);
}
