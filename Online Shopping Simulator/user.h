#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include <iomanip>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User {
public:
    User();
    //User(std::string name, double balance, int type);
    //added this
    User(std::string name, double balance, int type, unsigned long long hash);
    virtual ~User();

    double getBalance() const;
    std::string getName() const;
    void deductAmount(double amt);
    virtual void dump(std::ostream& os);
    //added this
    unsigned long long getHash();

private:
    std::string name_;
    double balance_;
    int type_;
    //added this
    unsigned long long hash_;
};
#endif
