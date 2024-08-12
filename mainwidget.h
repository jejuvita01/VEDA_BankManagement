#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>


class QPushButton;
class QLabel;

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

signals:
    void switchToLoginScreen();
    void switchToSignUpScreen();
    void switchToShowProductScreen();
    void quit();
};

#endif // MAINWIDGET_H
