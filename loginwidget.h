#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QObject>
#include <QWidget>
class QLineEdit;
class QPushButton;
class map;

class loginwidget : public QWidget
{
    Q_OBJECT
    QLineEdit *id;
    QLineEdit *pwd;
    map<string, pair<string, Person*>> sys;
public:
    loginwidget(QWidget *parent = nullptr, map<string, pair<string, Person*>> sys);
    void setData(map<string, pair<string, Person*>> sys);
    ~loginwidget();
};

#endif // LOGINWIDGET_H
