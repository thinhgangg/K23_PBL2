#pragma once
#define ACCOUNTMANAGER_H

#include "Account.h"
#include "Manager.h"
#include "Customer.h"
#include "Menu.h"
#include "Vector.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <iomanip>

class AccountManager {
private:
    Vector<string> readAllLines(const string& filename);
    void writeAllLines(const string& filename, const Vector<string>& lines);
    bool isValidUsername(const string& username);
    bool isUsernameTaken(const string& user);
    bool isValidPassword(const string& password);
    bool isValidName(const string& name);
    bool isValidPhone(const string& phone);
    bool isPhoneNumberTaken(const string& phone);
    string inputPassword();
    bool isdeleteAccount(const string& filename, const string& username);

public:
    void login();
    void registerAccount(const string& filename, const string& accountType);
    void resetPassword(const string& filename);
    void changePassword(const string& filename, const string& username);
    void changePhoneNumber(const string& filename, const string& username);
    void deleteAccount(const string& filename, const string& username);
    void searchCustomer();
    void viewCustomerList();
};
