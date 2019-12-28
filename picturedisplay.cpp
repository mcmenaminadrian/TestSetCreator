#include <QRect>
#include <QGraphicsRectItem>
#include <QPointF>
#include "picturedisplay.hpp"

using namespace std;

PictureDisplay::PictureDisplay(QWidget* parent):QGraphicsView(parent)
{
    xFrame = 10;
    yFrame = 10;
    scaleFactor = 100;
	QObject::connect(this, SIGNAL(signalUpdate()), this, SLOT(update()));
	displayScene = new QGraphicsScene();
	rectItem = nullptr;


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
    drawBoxFrame(_xFrame, _yFrame);
	setScene(displayScene);
	centerOn(xPic, yPic);
}

void PictureDisplay::drawBoxFrame(const int _xFrame, const int _yFrame)
{
	QPointF topCorner = mapToScene(QPoint(0, 0));
	if (rectItem) {
		rectItem->setRect(topCorner.rx() + xFrame,
            topCorner.ry() + yFrame, scaleFactor, scaleFactor);
	} else {
        rectItem = displayScene->addRect(QRect(10, 10, scaleFactor, scaleFactor),
			QPen(Qt::red));
		xFrame = 10;
		yFrame = 10;
	}

}

void PictureDisplay::paintEvent(QPaintEvent *event)
{
	QGraphicsView::paintEvent(event);
	drawBoxFrame(xFrame, yFrame);
}

void PictureDisplay::left()
{
	if (xFrame == 0) {
		return;
	}
	xFrame--;
	drawBoxFrame(xFrame, yFrame);
}

void PictureDisplay::up()
{
	if (yFrame == 0) {
		return;
	}
	yFrame--;
	drawBoxFrame(xFrame, yFrame);
}

void PictureDisplay::right()
{
	if (xFrame + 100 >= frameRect().width()) {
		return;
	}
	xFrame++;
	drawBoxFrame(xFrame, yFrame);
}

void PictureDisplay::down()
{
	if (yFrame + 100 >= frameRect().height()) {
		return;
	}
	yFrame++;
	drawBoxFrame(xFrame, yFrame);
}

QRect PictureDisplay::getFragment() const
{
	QPointF topCorner = mapToScene(0, 0);
	return QRect(xFrame + topCorner.rx(), yFrame + topCorner.ry(),
        scaleFactor, scaleFactor);
}

void PictureDisplay::reScaleFrame(const int scaleF)
{
    scaleFactor = 100 + scaleF * 3;
    drawBoxFrame(xFrame, yFrame);
}
