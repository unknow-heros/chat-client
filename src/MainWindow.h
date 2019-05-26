#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qwidget.h>

namespace Ui { class MainWindow; }

class MainWindow :public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *widget = nullptr);
	~MainWindow();

	void winClose();

	void initAction();

	void initUI();

	void setHeadImage(QString imagePath);

	void onOpenPersonalCenter();

	void onOpenChatWidget();

private:
	Ui::MainWindow* ui;
};
#endif // !MAINWINDOW_H
