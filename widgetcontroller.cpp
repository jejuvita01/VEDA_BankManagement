#include "widgetcontroller.h"
#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include "loginwidget.h"

WidgetController::WidgetController() {
    lgnwdg = new loginwidget;
    setCentralWidget(lgnwdg);
}
