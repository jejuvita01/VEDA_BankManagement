#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QWidget>

namespace Ui {
class ManagerWidget;
}

class ManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerWidget(QWidget *parent = nullptr);
    ~ManagerWidget();

private:
    Ui::ManagerWidget *ui;
};

#endif // MANAGERWIDGET_H
