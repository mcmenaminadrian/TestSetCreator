#include <QRect>
#include "picturedisplay.hpp"

using namespace std;

PictureDisplay::PictureDisplay(QWidget* parent):QGraphicsView(parent)
{
	xFrame = -1;
	yFrame = -1;
	QObject::connect(this, SIGNAL(signalUpdate()), this, SLOT(update()));
	displayScene = new QGraphicsScene();
	setScene(displayScene);
}

PictureDisplay::~PictureDisplay()
{
	delete displayScene;
}

void PictureDisplay::displayImage(const QImage* image, const int xPic,
	const int yPic, const int _xFrame, const int _yFrame)
{
	QPixmap bigPicture = QPixmap::fromImage(*image);
	displayScene->addPixmap(bigPicture);

	emit signalUpdate();
}
