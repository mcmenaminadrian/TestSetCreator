#ifndef PICTUREDISPLAY_HPP
#define PICTUREDISPLAY_HPP

#include <QObject>
#include <QWidget>
#include <QGraphicsView>

class PictureDisplay : public QGraphicsView
{

	Q_OBJECT

private:
	int xFrame;
	int yFrame;
	QGraphicsScene *displayScene;
	QGraphicsRectItem *rectItem;
	void drawBoxFrame(const int xFrame, const int yFrame);

public:
	PictureDisplay(QWidget *parent);
	~PictureDisplay();

protected:
	void paintEvent(QPaintEvent* event);

public slots:
	void displayImage(QImage*, int, int, int, int);

signals:
	void signalUpdate();

};

#endif // PICTUREDISPLAY_HPP
