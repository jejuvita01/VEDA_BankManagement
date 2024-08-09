#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

namespace Ui {
    class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::MainWidget *ui;
public:
    MainWidget(QWidget *parent = nullptr);
    Ui::MainWidget* getUi();
    ~MainWidget();
};

#endif // MAINWIDGET_H
