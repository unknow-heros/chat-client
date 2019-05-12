#ifndef CONTACTSCENTER_H_
#define CONTACTSCENTER_H_

#include <QWidget>

namespace Ui {
class ContactsCenter;
}

class ContactsCenter : public QWidget
{
    Q_OBJECT

public:
    explicit ContactsCenter(QWidget *parent = 0);
    ~ContactsCenter();

private:
    Ui::ContactsCenter *ui;
};

#endif // CONTACTSCENTER_H_
