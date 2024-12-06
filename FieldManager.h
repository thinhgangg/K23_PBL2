#pragma once
#define FIELDMANAGER_H

#include "Vector.h"
#include "Menu.h"
#include "FileManager.h"

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class FieldManager {
private:
    Vector<string> availableTimeSlots;
    Vector<string> availableFields;
    string timeSlot;
    string field;
    string customerName;
    string phone;
    string address;
    string paymentStatus;
    string price;

    struct Field {
        string timeSlot;
        string fieldName;
        int price;
    };

    void loadTimeSlots(const string& filename);
    void loadFields(const string& filename);
    void displayTimeSlots();
    void displayFields(const string& timeSlot);
    string selectTimeSlot();
    string selectField(const string& timeSlot);

    bool isFieldAvailable(const string& timeSlot, const string& field);
    bool isFieldBookedByUser(const string& filePath, const string& username);
    bool isBookField(const string& timeSlot, const string& field, const string& username, const string& customerName);
    bool isCancelBookField(const string& timeSlot, const string& field, const string& username);
    bool checkAvailableFields(const string& timeSlot);
    void viewFieldInfo(const string& timeSlot, const string& field, bool bill);
    void printBill(const string& timeSlot, const string& field);
    void logAction(const string& username, const string& action, const string& field, const string& timeSlot);
    string generateInvoiceNumber();
    
public:
    FieldManager();
    Vector<Field> fields;
    void loadFieldsFromFile(const string& filename);
    void saveFieldsToFile(const string& filename);
    void bookField(const string& username, const string& customerName);
    void cancelBookField(const string& username);
    void viewBookingHistory(const string& username);
    void viewAvailableFields();
    void viewFieldDetails();
    void viewAllFieldsPrice();
    void changeFieldsPrice();
    void viewAndPrintBill();
};
