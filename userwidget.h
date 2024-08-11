#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

namespace Ui {
class UserWidget;
}

class User;
class Person;

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();

    void setPerson(Person* person);
    void refreshTable();

private:
    Ui::UserWidget *ui;

    Person* person;
};

#endif // USERWIDGET_H
