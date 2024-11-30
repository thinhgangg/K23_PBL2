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
    Menu menu;
    menu.printGIO();

    for (size_t i = 0; i < availableTimeSlots.get_size(); ++i) {
        cout << "\t\t\t\t\t\t|                        " << i + 1 << ". " << availableTimeSlots[i] << "                        |" << endl;
        cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    }
    cout << "\t\t\t\t\t\t|                        0. GO BACK                            |" << endl;
    cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
}

void FieldManager::displayFields() {
    Menu menu;
    menu.printSAN();

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
        menu.printError();
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
        menu.printError();
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

            while (true) {
                system("cls");
                menu.printDATSAN();
                menu.printKHUNGGIO(timeSlot);
                menu.printTENSAN(field);
                if (booking.isBookField(timeSlot, field, username, customerName)) {
                    system("cls");
                    return;
                }
                else break;
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
        menu.printXEMSANTRONG();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) return;

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

void FieldManager::viewFieldDetails() {
    Menu menu;
    BookingManager booking;

    while (true) {
        system("cls");
        menu.printXEMSAN();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) return;

        while (true) {
            system("cls");
            menu.printXEMSAN();
            menu.printKHUNGGIO(timeSlot);
            string field = selectField(timeSlot);
            if (field.empty()) break;

            string filePath = "TimeSlots/" + timeSlot + "/" + field + ".txt";
            ifstream file(filePath);

            if (!file.is_open()) {
                system("cls");
                cout << "\t\t\t\t\t\tERROR: Unable to open file" << endl;
                menu.printRETURN();
                cin.ignore();
                cin.get();
                return;
            }

            string line;
            string status, price, username, customer, phone, payment, note;

            while (getline(file, line)) {
                stringstream ss(line);
                string label, value;
                getline(ss, label, ':');
                getline(ss, value);

                if (!value.empty()) {
                    if (value.front() == ' ') value.erase(value.begin());
                    if (value.back() == ' ') value.erase(value.end() - 1);
                }

                if (label == "STATUS") status = value;
                else if (label == "PRICE") price = value;
                else if (label == "USERNAME") username = value;
                else if (label == "CUSTOMER") customer = value;
                else if (label == "PHONE NUMBER") phone = value;
                else if (label == "PAYMENT DETAILS") payment = value;
                else if (label == "NOTE") note = value;
            }

            system("cls");
            menu.printXEMSAN();
            menu.printKHUNGGIO(timeSlot);
            menu.printTENSAN(field);

            if (status == "Available") {
                cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t|                    FIELD: " << setw(34) << left << field << " |" << endl;
                cout << "\t\t\t\t\t\t|                    STATUS: " << setw(33) << left << status << " |" << endl;
                cout << "\t\t\t\t\t\t|                    PRICE: " << setw(34) << left << price << " |" << endl;
                cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            } else if (status == "Booked") {
                cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t|                    FIELD: " << setw(34) << left << field << " |" << endl;
                cout << "\t\t\t\t\t\t|                    STATUS: " << setw(33) << left << status << " |" << endl;
                cout << "\t\t\t\t\t\t|                    PRICE: " << setw(34) << left << price << " |" << endl;
                cout << "\t\t\t\t\t\t|                    CUSTOMER: " << setw(31) << left << customer << " |" << endl;
                cout << "\t\t\t\t\t\t|                    PHONE NUMBER: " << setw(27) << left << phone << " |" << endl;
                cout << "\t\t\t\t\t\t|                    PAYMENT DETAILS: " << setw(24) << left << payment << " |" << endl;
                cout << "\t\t\t\t\t\t|                    NOTE: " << setw(35) << left << note << " |" << endl;
                cout << "\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            }
            
            menu.printRETURN();
            cin.ignore();
            cin.get();
            break;
        }
    }
}





