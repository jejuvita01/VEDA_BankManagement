#ifndef WIDGETCONTROLLER_H
#define WIDGETCONTROLLER_H

#include <QMainWindow>
#include <QWidget>
class QObject;
class loginwidget;

class WidgetController : public QMainWindow
{
    Q_OBJECT
private:
    loginwidget* lgnwdg;
public:
    WidgetController(QWidget* parent = nullptr);
    ~WidgetController();
};

#endif // WIDGETCONTROLLER_H
