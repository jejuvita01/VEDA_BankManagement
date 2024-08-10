#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include <QWidget>

#include <vector>
#include <string>
using namespace std;

namespace Ui {
class SignUpWidget;
}

class QLabel;

class SignUpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpWidget(QWidget *parent = nullptr);
    ~SignUpWidget();
    void insertData(vector<string> data);

private:
    Ui::SignUpWidget *ui;
    bool idCheck;
    bool pwCheck;
    QList<QString> ids;

    void setMessageLabel(QLabel* label, QString message, QString styleSheet);

public slots:
    void checkIdAndPw();            // 완료 버튼 누를 때 확인하기
    void checkPwCheck(const QString& text);            // 비밀번호 재확인 입력 시
    void checkId();


signals:
    void switchToMainScreen();
};

#endif // SIGNUPWIDGET_H
