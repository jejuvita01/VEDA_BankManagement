#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>
#include <string>
using namespace std;
namespace Ui {
class UserWidget;
}

class User;
class Person;
class QFormLayout;
class QLineEdit;
class QComboBox;
class QPushButton;
class QSpinBox;
class QStackedLayout;
class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();

    void setPerson(Person* person);
    void setId(string id);
    void refreshTable();

private:
    Ui::UserWidget *ui;

    string id;
    Person* person;

    QStackedLayout* stackedLayout;

    QWidget* depositWidget;
    QFormLayout* depositLayout;
    QSpinBox* depositBalanceSpinBox;
    QPushButton* depositCompleteButton;

    QWidget* savingWidget;
    QFormLayout* savingLayout;
    QSpinBox* savingBalanceSpinBox;
    QSpinBox* savingDurationSpinBox;
    QPushButton* savingCompleteButton;

signals:
    void switchToMainScreen();
    void withdrawUser(string id);
};

#endif // USERWIDGET_H
