#ifndef WIDGETCONTROLLER_H
#define WIDGETCONTROLLER_H
#include <QMainWindow>
#include <QWidget>
#include <map>
#include <string>
#include "loginwidget.h"
#include "mainwidget.h"

using namespace std;

class QObject;
class LoginWidget;
class Person;
class MainWidget;

namespace Ui {
class MainWidget;
class LoginWidget;
}

class WidgetController : public QMainWindow
{
    Q_OBJECT
private:
    MainWidget *mainwdg;
    LoginWidget* lgnwdg;
    map<string, pair<string, Person*>> data; // id: <pw,person>
public:
    WidgetController(QWidget* parent = nullptr);
    void set_data(map<string, pair<string, Person*>> data);
    ~WidgetController();
};
#endif // WIDGETCONTROLLER_H














