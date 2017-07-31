#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsScene;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QString jpegFile;
	QGraphicsScene *displayScene;

public slots:
	void showImage(QImage *picture, const uint64_t xImage,
		const uint64_t yImage, const uint64_t xFrame,
		const uint64_t yFrame);
};

#endif // MAINWINDOW_H
