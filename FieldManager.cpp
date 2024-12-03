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

void FieldManager::loadFieldsFromFile(const string& filename) {
    ifstream inputFile(filename);
    string line;

    if (!inputFile.is_open()) {
        cerr << "Could not open the file!" << endl;
        return;
    }

    fields.clear();

    while (getline(inputFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos) {
            string timeSlot = line.substr(0, pos1);
            string fieldName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int price = stoi(line.substr(pos2 + 1));

            fields.push_back({timeSlot, fieldName, price});
        }
    }

    inputFile.close();
}

void FieldManager::saveFieldsToFile(const string& filename) {
    ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        cerr << "Could not open the file to save!" << endl;
        return;
    }

    for (const auto& fieldData : fields) {
        outputFile << fieldData.timeSlot << "," << fieldData.fieldName << "," << fieldData.price << endl;
    }

    outputFile.close();
}

void FieldManager::displayTimeSlots() {
    Menu menu;
    menu.printGIO();

    for (size_t i = 0; i < availableTimeSlots.get_size(); ++i) {
        cout << "\t\t\t\t\t\t\t\t|                        " << i + 1 << ". " << availableTimeSlots[i] << "                        |" << endl;
        cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    }
    cout << "\t\t\t\t\t\t\t\t|                        0. GO BACK                            |" << endl;
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
}

void FieldManager::displayFields() {
    Menu menu;
    menu.printSAN();
    loadFieldsFromFile("fields_details.txt");
    for (size_t i = 0; i < availableFields.get_size(); ++i) {
        string field = availableFields[i];

        int fieldPrice = 0;
        for (const auto& fieldData : fields) {
            if (fieldData.fieldName == field) {
                fieldPrice = fieldData.price;
                break;
            }
        }

        cout << "\t\t\t\t\t\t\t\t|            " << i + 1 << ". " << field << "           |          " << fieldPrice << " VND          |" << endl;
        cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    }
    cout << "\t\t\t\t\t\t\t\t|                           0. GO BACK                         |" << endl;
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
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
            cout << "\t\t\t\t\t\t\t                     NO AVAILABLE FIELDS IN THIS TIME SLOT!" << endl;
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
                cout << "\t\t\t\t\t\t\t\tERROR: Unable to open file" << endl;
                menu.printRETURN();
                cin.ignore();
                cin.get();
                return;
            }

            string line;
            string status, price, username, customer, phone, address, payment, note;

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
                else if (label == "ADDRESS") address = value;
                else if (label == "PAYMENT DETAILS") payment = value;
                else if (label == "NOTE") note = value;
            }

            system("cls");
            menu.printXEMSAN();
            menu.printKHUNGGIO(timeSlot);
            menu.printTENSAN(field);

            if (status == "Available") {
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    FIELD: " << setw(34) << left << field << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    STATUS: " << setw(33) << left << status << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    PRICE: " << setw(34) << left << price << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            } else if (status == "Booked") {
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    FIELD: " << setw(34) << left << field << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    STATUS: " << setw(33) << left << status << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    PRICE: " << setw(34) << left << price << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    CUSTOMER: " << setw(31) << left << customer << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    PHONE NUMBER: " << setw(27) << left << phone << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    ADDRESS: " << setw(22) << left << address << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    PAYMENT DETAILS: " << setw(24) << left << payment << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                    NOTE: " << setw(35) << left << note << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            }
            
            menu.printRETURN();
            cin.ignore();
            cin.get();
            break;
        }
    }
}

void FieldManager::viewAllFieldsPrice() {
    system("cls");
    Menu menu;
    menu.printGIASAN();

    string currentTimeSlot = "";

    for (const auto& fieldData : fields) {
        if (fieldData.timeSlot != currentTimeSlot) {
            cout << "\n" << setw(11) << left << "\t\t\t\t\t\t\t\t\t\t     Time Slot: " << fieldData.timeSlot << endl;
            cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            currentTimeSlot = fieldData.timeSlot;
        }

        cout << setw(7) << left << "\t\t\t\t\t\t\t\t\t\t  Field: " 
             << setw(6) << left << fieldData.fieldName 
             << "| " 
             << setw(5) << left << "Price: "
             << setw(6) << left << fieldData.price << " VND" << endl;
    }
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;

    menu.printRETURN();
    cin.ignore();
    cin.get();
}

void FieldManager::changeFieldsPrice() {
    Menu menu;
    BookingManager booking;

    while (true) {
        system("cls");
        menu.printDOIGIA();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) return;

        while (true) {
            system("cls");
            menu.printDOIGIA();
            menu.printKHUNGGIO(timeSlot);
            string field = selectField(timeSlot);
            if (field.empty()) break;

            while (true) {
                system("cls");
                menu.printDATSAN();
                menu.printKHUNGGIO(timeSlot);
                menu.printTENSAN(field);

                if (!booking.isFieldAvailable(timeSlot, field)) {
                    system("cls");
                    cout << "\t\t\t\t\t\t\t\t     THIS FIELD IS NOT AVAILABLE. CANNOT CHANGE THE PRICE!" << endl;
                    menu.printRETURN();
                    cin.ignore();
                    cin.get();
                    break;
                }


                int newPrice;
                cout << "\t\t\t\t\t\t\t\t\t    ENTER THE NEW PRICE FOR " << field << ": ";
                cin >> newPrice;

                bool found = false;
                for (auto& f : fields) {
                    if (f.timeSlot == timeSlot && f.fieldName == field) {
                        f.price = newPrice;
                        found = true;
                        break;
                    }
                }

                if (found) {
                    saveFieldsToFile("fields_details.txt");
                    system("cls");
                    cout << "\t\t\t\t\t\t\t\t\t           PRICE UPDATE SUCCESSFULLY!" << endl;
                    menu.printRETURN();
                } else {
                    system("cls");
                    cout << "\t\t\t\t\t\t\t\t\t                FIELD NOT FOUND!" << endl;
                    menu.printRETURN();
                }
                cin.ignore();
                cin.get();
                return;
            }
        }
    }
}

// void FieldManager::printBillAndFreeField(const string& timeSlot, const string& field, const string& username) {
//     Menu menu;
//     string filePath = "TimeSlots/" + timeSlot + "/" + field + ".txt";
//     ifstream file(filePath);

//     if (!file.is_open()) {
//         system("cls");
//         cout << "\t\t\t\t\t\t\t\tERROR: Unable to open file " << filePath << endl;
//         menu.printRETURN();
//         cin.ignore();
//         cin.get();
//         return;
//     }

//     string line;
//     string customerName, phone, paymentStatus, note;
//     int price = 0;

//     while (getline(file, line)) {
//         if (line.find("FIELD: ") != string::npos) {
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         } else if (line.find("STATUS: Booked") != string::npos) {
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         } else if (line.find("PRICE: ") != string::npos) {
//             price = stoi(line.substr(7));
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         } else if (line.find("USERNAME: ") != string::npos) {
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         } else if (line.find("CUSTOMER: ") != string::npos) {
//             customerName = line.substr(10);
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         } else if (line.find("PHONE NUMBER: ") != string::npos) {
//             phone = line.substr(14);
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         } else if (line.find("PAYMENT DETAILS: ") != string::npos) {
//             paymentStatus = line.substr(17);
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         } else if (line.find("NOTE: ") != string::npos) {
//             note = line.substr(6);
//             cout << "\t\t\t\t\t\t\t\t" << line << endl;
//         }
//     }
//     file.close();

//     cout << "\t\t\t\t\t\t\t\t--------------------------------------------" << endl;
//     cout << "\t\t\t\t\t\t\t\tTOTAL: " << price << " VND" << endl;
//     cout << "\t\t\t\t\t\t\t\t--------------------------------------------" << endl;

//     ofstream outFile(filePath, ios::trunc);
//     if (outFile.is_open()) {
//         outFile << "FIELD: " << field << endl;
//         outFile << "STATUS: Available" << endl;
//         outFile << "PRICE: " << price << " VND" << endl;
//         outFile << "USERNAME: " << username << endl;
//         outFile << "CUSTOMER: " << customerName << endl;
//         outFile << "PHONE NUMBER: " << phone << endl;
//         outFile << "PAYMENT DETAILS: " << paymentStatus << endl;
//         outFile << "NOTE: " << note << endl;
//         outFile.close();

//         system("cls");
//         cout << "\t\t\t\t\t\t\t\tThe bill has been printed and field is now Free." << endl;
//         menu.printRETURN();
//         cin.ignore();
//         cin.get();
//     } else {
//         system("cls");
//         cout << "\t\t\t\t\t\t\t\tERROR: Unable to write to file " << filePath << endl;
//         menu.printRETURN();
//         cin.ignore();
//         cin.get();
//     }
// }