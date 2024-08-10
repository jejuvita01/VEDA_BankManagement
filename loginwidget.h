#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include <map>
#include <string>

using namespace std;
#include <QWidget>


namespace Ui {
class LoginWidget;
}
class QLineEdit;
class QPushButton;
class Person;
class User;
class Manager;

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    void setData(map<string, pair<string, Person*>> d);

private:
    Ui::LoginWidget *ui;
    map<string, pair<string, Person*>> data;
signals:
    void switchToMainScreen();
    void switchToUserScreen();
    void switchToManagerScreen();

public slots:
    void login();
};

#endif // LOGINWIDGET_H
