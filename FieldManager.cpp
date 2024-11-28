#include "FieldManager.h"
#include <iostream>

using namespace std;

FieldManager::FieldManager() {
    loadTimeSlots("timeslots.txt");

    loadFields("fields.txt");
}

void FieldManager::loadTimeSlots(const string& filename) {
    FileManager fileManager;
    Vector<string> data = fileManager.loadData(filename);

    for (size_t i = 0; i < data.get_size(); ++i) {
        const string& timeSlot = data[i];
        availableTimeSlots.push_back(timeSlot);
    }
}

void FieldManager::loadFields(const string& filename) {
    FileManager fileManager;
    Vector<string> data = fileManager.loadData(filename);

    for (size_t i = 0; i < data.get_size(); ++i) {
        availableFields.push_back(data[i]);
    }
}

void FieldManager::displayTimeSlots() {
    cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t|                     AVAILABLE TIME SLOTS                     |" << endl;
    cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;

    for (size_t i = 0; i < availableTimeSlots.get_size(); ++i) {
        cout << "\t\t\t\t\t\t|                        " << i + 1 << ". " << availableTimeSlots[i] << "                        |" << endl;
        cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    }
    cout << "\t\t\t\t\t\t|                        0. GO BACK                            |" << endl;
    cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
}

void FieldManager::displayFields() {
    cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t|                       AVAILABLE FIELDS                       |" << endl;
    cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;

    for (size_t i = 0; i < availableFields.get_size(); ++i) {
        cout << "\t\t\t\t\t\t|                           " << i + 1 << ". " << availableFields[i] << "                           |" << endl;
        cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    }
    cout << "\t\t\t\t\t\t|                           0. GO BACK                         |" << endl;
    cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
}

string FieldManager::selectTimeSlot() {
    Menu menu;
    displayTimeSlots();
    int timeSlotChoice;
    cin >> timeSlotChoice;

    if (timeSlotChoice == 0) {
        return "";
    } else if (timeSlotChoice > 0 && timeSlotChoice <= availableTimeSlots.get_size()) {
        return availableTimeSlots[timeSlotChoice - 1];
    } else {
        menu.displayError();
        return selectTimeSlot();
    }
}

string FieldManager::selectField(const string& timeSlot) {
    Menu menu;
    displayFields();
    int fieldChoice;
    cin >> fieldChoice;

    if (fieldChoice == 0) {
        return "";
    } else if (fieldChoice > 0 && fieldChoice <= availableFields.get_size()) {
        return availableFields[fieldChoice - 1];
    } else {
        menu.displayError();
        return selectField(timeSlot);
    }
}

void FieldManager::bookField(const string& username, const string& customerName) {
    Menu menu;
    BookingManager booking;

    while (true) {
        system("cls");
        menu.printDATSAN();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) return;

        while (true) {
            system("cls");
            menu.printDATSAN();
            menu.printKHUNGGIO(timeSlot);
            string field = selectField(timeSlot);
            if (field.empty()) break;

            if (booking.isBookField(timeSlot, field, username, customerName)) {
                system("cls");
                return;
            }
        }
    }
}

void FieldManager::cancelBookField(const string& username) {
    Menu menu;
    BookingManager booking;

    while (true) {
        system("cls"); 
        menu.printHUYSAN();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) return;

        while (true) {
            system("cls"); 
            menu.printHUYSAN();
            menu.printKHUNGGIO(timeSlot);
            string field = selectField(timeSlot);
            if (field.empty()) break;

            if (booking.isCancelBookField(timeSlot, field, username)) {
                system("cls");
                return;
            }
        }
    }
}

void FieldManager::viewAvailableFields() {
    Menu menu;
    BookingManager booking;

    while (true) {
        system("cls"); 
        menu.printXEMSAN();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) {
            system("cls");
            return;
        }

        system("cls");
        if (!booking.checkAvailableFields(timeSlot)) {
            cout << "\t\t\t\t\t                     NO AVAILABLE FIELDS IN THIS TIME SLOT!                   " << endl;
            menu.printRETURN();
        } else {
            menu.printRETURN();
        }
        cin.ignore();
        cin.get();
    }
}
