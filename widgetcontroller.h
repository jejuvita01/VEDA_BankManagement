#ifndef WIDGETCONTROLLER_H
#define WIDGETCONTROLLER_H

class QMainWindow;
class QWidget;
class QObject;
class loginwidget;

class WidgetController : public QMainWindow
{
    Q_OBJECT
private:
    loginwidget* lgnwdg;
public:
    WidgetController();
    ~WidgetController();
};

#endif // WIDGETCONTROLLER_H
