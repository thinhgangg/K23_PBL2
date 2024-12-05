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
    // Constructors
    Account();
    Account(string user, string pass, string name, string phone, string address);

    void setUsername(const string& user) { username = user; }

    // Getters
    string getUsername() const { return username; }
    // string getName() const { return name; }
    // string getPhoneNumber() const { return phoneNumber; }

    // Static methods
    static bool accountExists(const string& filename, const string& user);
    bool getUserInfo(const string &filename, const string &user, const string &pass, string &name);
    bool isAdminUser(const string& username, const string& filename);

    // Virtual method
    virtual void saveAccount(const string& filename) const;
};
