#include "widgetcontroller.h"

#include <QApplication>
using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    WidgetController *wdgctrl = new WidgetController();
    wdgctrl->show();
    return a.exec();
}
