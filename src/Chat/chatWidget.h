#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>

namespace Ui {
	class chatWidget;
}

class chatWidget : public QWidget
{
	Q_OBJECT

public:
	explicit chatWidget(QWidget *parent = nullptr);
	~chatWidget();

public:
	void initAction();
	
public slots:
	void switchWin();


private:
	Ui::chatWidget *ui;

signals:
	void interviewShow();

};

#endif // CHATWIDGET_H
