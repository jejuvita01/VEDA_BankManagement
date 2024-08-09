/*
 로그인 : map <아이디, 비밀번호>
 계좌(account) class - 예금(deposit), 적금(saving) (상속)
 사람(person) class? - 관리자(manager), 사용자(user) (상속)

 관리자로 로그인하면 >> 사용자 조회 가능?
 사용자 전체 조회 / 찾기 조회 (사용자 계좌 정보 출력, 사용자 삭제)

 사람 >>  잔액 조회, 입금, 출금, 계좌 개설(예/적금), 탈퇴


 사람 - 계좌(account) 간 연결: 사용자한테 계좌를 달아주기.
 포인터로 예적금 만들때마다 넣어주기.

 계좌 - 잔액, 입금/출금 동작, (적금: 이자, 해지)


 파일 입출력: 사용자 & 계좌 정보


 사람 ( 계좌 )

 // Account_manager? - 전체 계좌 보는 기능 (????)


 ** 역할 분담 **

서현 - Person class (User, Manager 상속 만들기)
성민 - Account class (Deposit, Saving 상속 만들기)

 */
#ifndef person_h
#define person_h

#include <string>
#include <vector>
using namespace std;
class Account;

class Person {
protected:
    string name;
    int age;
public:
    Person();
    Person(string, int);
    void set_name(string);
    void set_age(int);
    string get_name();
    int get_age();
    virtual void make_deposit() = 0;
    virtual void make_saving() = 0;
    virtual void insert_deposit(int) = 0;
    virtual void insert_saving(int, int) = 0;
    virtual void insert_deposit(int, time_t) = 0;
    virtual void insert_saving(int, int, time_t) = 0;
    virtual vector<Account*>& get_accounts() = 0;
    virtual ~Person();
};


#endif /* person_h */
