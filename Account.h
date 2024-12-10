#pragma once

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
    Account(const string& user, const string& pass, const string& name, const string& phone, const string& address);
    bool getUserInfo(const string& filename, const string& user, const string& pass, string& name);
    bool isAdminUser(const string& username, const string& filename);
    static bool accountExists(const string& filename, const string& user);
    virtual void saveAccount(const string& filename) const;
};
