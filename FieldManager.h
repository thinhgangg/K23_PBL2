#pragma once
#define FIELDMANAGER_H

#include "Vector.h"
// #include <vector>
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

    // mới
    struct Field {
        string timeSlot;
        string fieldName;
        int price;
    };

    Vector<Field> fields;

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
    void viewFieldDetails();

    // mới
    void viewAllFieldsPrice();
    void changeFieldsPrice();

    void loadFieldsFromFile(const string& filename);
    void saveFieldsToFile(const string& filename);
};
