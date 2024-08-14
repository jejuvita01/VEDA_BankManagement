#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <map>
#include <string>
using namespace std;

#include <QWidget>

class Person;
class QTableWidgetItem;

namespace Ui {
class ManagerWidget;
}

class ManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerWidget(QWidget *parent = nullptr);
    ~ManagerWidget();
    void setData(map<string, pair<string, Person*>> d);
    void setPerson(Person* person);
    void setId(string id);

private:
    Ui::ManagerWidget *ui;

    map<string, pair<string, Person*>> data; // id: <pw,person>
    string id;
    Person* person;

    void refreshUserSearchTable(string searchId);
    void refreshUserDeleteTable();

signals:
    void switchTomainScreen();
    void withdrawManager(string id);
    void withdrawUser(string id);

public slots:
    void refreshUserAccountsTable(QTableWidgetItem* item);
};

#endif // MANAGERWIDGET_H
