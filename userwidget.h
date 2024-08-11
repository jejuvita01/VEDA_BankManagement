#ifndef USERWIDGET_H
#define USERWIDGET_H

#include <QWidget>

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
    void refreshTable();

private:
    Ui::UserWidget *ui;

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
};

#endif // USERWIDGET_H
