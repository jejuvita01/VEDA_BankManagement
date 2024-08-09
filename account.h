#ifndef account_h
#define account_h

class Account {
protected:
    time_t startDate;
    int balance;
    int interest;
public:
    Account();
    Account(int);
    Account(int, time_t);
    virtual void show_info();
    virtual void calculate_interest() = 0;
    virtual bool deposit(int money);
    virtual bool withdraw(int money);
    virtual string who_is_this() = 0;
    virtual time_t get_start_date();
    virtual int get_balance();
    virtual int get_duration() = 0;
    virtual ~Account();
};

#endif
