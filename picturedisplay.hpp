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

public:
	PictureDisplay(QWidget *parent);
	~PictureDisplay();

protected:

public slots:
	void displayImage(const QImage*, const int, const int,
		const int, const int);

signals:
	void signalUpdate();

};

#endif // PICTUREDISPLAY_HPP
