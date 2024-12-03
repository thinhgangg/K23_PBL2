#pragma once
#define MENU_H

#include "AccountManager.h"
#include "FieldManager.h"
#include "BookingManager.h"
#include <string>
using namespace std;

class Menu {
public:
    void displayIntro();
    void displayLogo();
    void displayGoodbye();
    
    void homeMenu();
    void managerMenu(const string& username, const string& customerName);
    void customerMenu(const string& username, const string& customerName);

    void resetPassMenu();
    void registrationMenu();
    void accountManagementMenu();

    void printDATSAN();
    void printHUYSAN();
    void printGIO();
    void printSAN();
    void printXEMSAN();
    void printXEMSANTRONG();
    void printGIASAN();
    void printDOIGIA();
    void printHOADON();
    void printKHUNGGIO(const string& timeSlot);
    void printTENSAN(const string& field);
    void printRETURN();

    void displaySignIn();
    void displaySignUp();
    void displayResetPass();
    void displayChangePass();
    void displayChangePhone();
    void printError();
    void displayBookingForm();
    void displaySearchCustomer();

    void customerInfoMenu(const string& username, const string& name, const string& phone, const string& address);
    void accountSettingsMenu(const string& username, bool isAdmin);

    void customerDetailsMenu();
    void fieldDetailsMenu();
};
