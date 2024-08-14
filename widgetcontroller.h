#ifndef WIDGETCONTROLLER_H
#define WIDGETCONTROLLER_H
#include <QMainWindow>
#include <QWidget>
#include <map>
#include <string>
using namespace std;

class QObject;
class LoginWidget;
class MainWidget;
class SignUpWidget;
class UserWidget;
class ManagerWidget;
class ShowProducts;
class Person;

#define PATH "./../../person_data.txt"

class WidgetController : public QMainWindow
{
    Q_OBJECT
private:
    MainWidget* mainwdg;
    LoginWidget* lgnwdg;
    SignUpWidget* sgnupwdg;
    UserWidget* userwdg;
    ManagerWidget* mngwdg;
    ShowProducts* showwdg;
    map<string, pair<string, Person*>> data; // id: <pw,person>
public:
    WidgetController(QWidget* parent = nullptr);
    void set_data(map<string, pair<string, Person*>> data);
    void init_data();
    void save_data();
    ~WidgetController();
};
#endif // WIDGETCONTROLLER_H
