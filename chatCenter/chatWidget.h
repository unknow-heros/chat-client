#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "ui_chatWidget.h"

class chatWidget : public QWidget
{
	Q_OBJECT

public:
	chatWidget(QWidget *parent = 0);
	~chatWidget();

private:
	Ui::chatWidget ui;
};

#endif // CHATWIDGET_H
