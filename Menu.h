#pragma once
#define MENU_H

#include "AccountManager.h"
#include "FieldManager.h"
#include "BookingManager.h"
#include <string>
using namespace std;

class Menu {
public:
    void homeMenu();
    void managerMenu(const string& username, const string& name);
    void customerMenu(const string& username, const string& name);

    void resetPassMenu();
    void registrationMenu();

    void displayLogo();
    void displayGoodbye();
    void displayTimeSlots();
    void displayFieldList();

    void printDATSAN();
    void printHUYSAN();
    void printKHUNGGIO(const string& timeSlot);
    void printXEMSAN();
    void printRETURN();

    void displaySignIn();
    void displaySignUp();
    void displayResetPass();
    void displayChangePass();
    void displayChangePhone();
    void displayError();
    void displayBookingForm();

    void customerDetailMenu(const string& username, const string& name, const string& phone);
    void accountSettingsMenu(const string& username);
};
