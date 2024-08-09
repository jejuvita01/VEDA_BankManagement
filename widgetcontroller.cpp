#include "loginwidget.h"
#include "widgetcontroller.h"

#include <QWidget>
#include <QObject>
#include <QMainWindow>

WidgetController::WidgetController(QWidget* parent)
    : QMainWindow(parent)
{
    lgnwdg = new loginwidget(this);
    setCentralWidget(lgnwdg);
}

WidgetController::~WidgetController() {

}
