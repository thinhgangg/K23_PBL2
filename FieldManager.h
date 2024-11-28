#pragma once
#define FIELDMANAGER_H

#include "Vector.h"
#include "Menu.h"
#include "FileManager.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

class FieldManager {
private:
    Vector<string> availableTimeSlots;
    Vector<string> availableFields;
public:
    FieldManager();

    void loadTimeSlots(const string& filename);
    void loadFields(const string& filename);

    void displayTimeSlots();
    void displayFields();

    string selectTimeSlot();
    string selectField(const string& timeSlot);

    void bookField(const string& username, const string& customerName);
    void cancelBookField(const string& username);
    void viewAvailableFields();
};
