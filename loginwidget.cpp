#include "loginwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QtWidgets>
#include <QApplication>
#include <map>
#include "Person.h"

loginwidget::loginwidget(QWidget *parent) // map; id: <pw,person>
    : QWidget(parent)
{
    QStringList labels;
    labels << "&Id" << "&Pasword";
    id = new QLineEdit(this);
    pwd = new QLineEdit(this);
    QFormLayout *formLayout = new QFormLayout;
    pwd->setEchoMode(QLineEdit::Password);
    formLayout->addRow(labels.at(0), id);
    formLayout->addRow(labels.at(1), pwd);

    QPushButton *lgnBtn = new QPushButton("login");
    lgnBtn->setCheckable(true);
    // lgnBtn->show();
    // connect(lgnBtn, &QPushButton::clicked, [=]() {
    //     if (sys.find(id) != sys.end() && sys.find(id) == pw) {
    //         if (dynamic_cast<User*>(sys.find(id).second.second)) {

    //         }
    //     }
    // });

    formLayout->addRow("", lgnBtn);

    QGroupBox *groupBox = new QGroupBox("&Sign in", this);
    groupBox->move(5, 5);
    groupBox->setLayout(formLayout);

    resize(groupBox->sizeHint().width() + 10, groupBox->sizeHint().height() + 10);

    connect(id, &QLineEdit::editingFinished, [&]() { qDebug() << "id changed " << id->text(); });
    connect(pwd, &QLineEdit::textChanged, [&](const QString &text) {
        //qDebug() << "pwd changed " << text;
        //qDebug() << id->text();
    });
}

// void loginwidget::setData(map<string, pair<string, Person*>> sys)
// {
//     this->sys = sys;
// }


loginwidget::~loginwidget() {}
