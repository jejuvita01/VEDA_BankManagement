#ifndef user_h
#define user_h

#include "person.h"
class Account;

class User : public Person {
    vector<Account*> accounts;
public:
    User();
    User(string, int);
    void deposit();
    void withdraw();
    virtual void show_all_account();
    virtual void make_saving();
    virtual void make_deposit();
    virtual void insert_deposit(int);
    virtual void insert_saving(int, int);
    virtual void insert_deposit(int, time_t);
    virtual void insert_saving(int, int, time_t);
    virtual string who_is_this();
    virtual vector<Account*>& get_accounts();
    virtual ~User();
};

#endif /* user_h */
