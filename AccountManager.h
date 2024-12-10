#pragma once

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
#include <stdexcept>

const string ERROR_INVALID_USERNAME = "\033[14;53HUSERNAME MUST BE AT LEAST 6 CHARACTERS LONG, AND CONTAIN NO SPACES OR SPECIAL CHARACTERS!";
const string ERROR_EXISTS_USERNAME = "\033[14;76HUSERNAME ALREADY EXISTS! TRY ANOTHER ONE!";
const string ERROR_INVALID_PASSWORD = "\033[14;75HPASSWORD MUST BE AT LEAST 6 CHARACTERS LONG!";
const string ERROR_INVALID_NAME = "\033[14;82HINVALID NAME! PLEASE TRY AGAIN!";
const string ERROR_INVALID_PHONENUMBER = "\033[14;78HINVALID PHONE NUMBER! PLEASE TRY AGAIN!";
const string ERROR_EXISTS_PHONENUMBER = "\033[14;78HTHIS PHONE NUMBER ALREADY REGISTERED!";

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
