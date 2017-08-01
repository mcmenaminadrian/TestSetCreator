#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;
class MasterJPEG;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	std::pair<int, int> getXYFrame() const;

private:
	Ui::MainWindow *ui;
	QString jpegFile;
	QGraphicsScene *displayScene;
	int xFrame;
	int yFrame;
	MasterJPEG *bigJPEG;

public slots:
	void displayInitialImage();

signals:
	void showImage(const QImage* pic, const int xPic, const int yPic,
		const int xFrame, const int yFrame);
};

#endif // MAINWINDOW_H
