#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QObject>
#include <QWidget>
class QLineEdit;
class QPushButton;

class loginwidget : public QWidget
{
    Q_OBJECT
    QLineEdit *id;
    QLineEdit *pwd;
public:
    loginwidget(QWidget *parent = nullptr);
    ~loginwidget();
};

#endif // LOGINWIDGET_H
