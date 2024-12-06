#pragma once
#define ACCOUNT_H

#include <fstream>
#include <string>
using namespace std;

class Account {
private:

protected:
    string name;
    string phoneNumber;
    string username;
    string password;
    string address;

public:
    Account();
    Account(string user, string pass, string name, string phone, string address);
    string getUsername() const { return username; }
    bool getUserInfo(const string &filename, const string &user, const string &pass, string &name);
    bool isAdminUser(const string& username, const string& filename);
    static bool accountExists(const string& filename, const string& user);
    virtual void saveAccount(const string& filename) const;
};
