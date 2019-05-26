#ifndef LINEEDITWITHBUTTON_H
#define LINEEDITWITHBUTTON_H

#include <QPushButton>
#include "CompleteLineEdit.h"


class LineEditWithButton : public CompleteLineEdit
{
	Q_OBJECT

public:
	LineEditWithButton(QWidget *parent);
	LineEditWithButton(bool isleft, QWidget *parent = 0);

	~LineEditWithButton();
public:
	void setButtonImage(QString icon);

protected:
	void resizeEvent(QResizeEvent* e);
	void enterEvent(QEvent* e);
	bool eventFilter(QObject* o, QEvent* e);
	void leaveEvent(QEvent* e);


private:
	QPushButton * m_button;
	bool m_enter;
};

#endif // LINEEDITWITHBUTTON_H
