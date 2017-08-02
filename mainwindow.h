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

public:
	MasterJPEG *bigJPEG;

public slots:
	void displayInitialImage();

signals:
	void showImage(QImage* pic, const int xPic, const int yPic,
		const int xFrame, const int yFrame);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
private slots:
	void on_pushButton_3_clicked();
	void on_pushButton_4_clicked();
	void on_pushButton_5_clicked();
	void on_pushButton_6_clicked();
};

#endif // MAINWINDOW_H
