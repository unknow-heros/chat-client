/*
 *     面试界面
*/

#ifndef INTERVIEWWIDGET_H
#define INTERVIEWWIDGET_H

#include <QWidget>

namespace Ui {
class interviewWidget;
}

class interviewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit interviewWidget(QWidget *parent = nullptr);
    ~interviewWidget();

private:
    Ui::interviewWidget *ui;
};

#endif // INTERVIEWWIDGET_H
