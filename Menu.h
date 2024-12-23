#pragma once

#include "AccountManager.h"
#include "FieldManager.h"

#include <string>
using namespace std;

class Menu {
private:
    void displayLogo();
    void displayGoodbye();
    void registrationMenu();
    void resetPassMenu();
    void accountManagementMenu();
    void accountSettingsMenu(const string& username, bool isAdmin);
    void invoiceMenu();
    void customerDetailsMenu();
    void fieldDetailsMenu(const string& username);

public:
    void displayIntro();
    void homeMenu();
    void managerMenu(const string& username, const string& name);
    void customerMenu(const string& username, const string& name);
    void displaySignIn();
    void displaySignUp();
    void displayResetPass();
    void displayChangePass();
    void displayChangePhone();
    void displaySearchCustomer();
    void displaySearchInvoice();
    void displayBookingForm();
    void printGIO();
    void printSAN();
    void printKHUNGGIO(const string& timeSlot);
    void printTENSAN(const string& field);
    void printDATSAN();
    void printHUYSAN();
    void printXEMSAN();
    void printXEMSANTRONG();
    void printGIASAN();
    void printDOIGIA();
    void printINHOADON();
    void printTIMKIEMHOADON();
    void printRETURN();
    void printError();
    void customerOptionMenu(const string& username, const string& name, const string& phone, const string& address);
};
