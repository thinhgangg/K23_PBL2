#include "FieldManager.h"

using namespace std;

FieldManager::FieldManager() {
    loadTimeSlots("timeslots.txt");

    loadFieldsName("fields.txt");
}

void FieldManager::loadTimeSlots(const string& filename) {
    Vector<string> data = readLinesFromFile(filename);

    for (size_t i = 0; i < data.get_size(); ++i) {
        const string& timeSlot = data[i];
        availableTimeSlots.push_back(timeSlot);
    }
}

void FieldManager::loadFieldsName(const string& filename) {
    Vector<string> data = readLinesFromFile(filename);

    for (size_t i = 0; i < data.get_size(); ++i) {
        availableFields.push_back(data[i]);
    }
}

Vector<string> FieldManager::readLinesFromFile(const string& filePath) {
    Menu menu;
    Vector<string> data;
    ifstream file(filePath);

    if (!file.is_open()) {
        system("cls");
        cout << "\t\t\t\t\t\tERROR: Unable to open file " << filePath << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return data;
    }

    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }

    file.close();
    return data;
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
        size_t pos1 = line.find(';');
        size_t pos2 = line.find(';', pos1 + 1);
        
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
        outputFile << fieldData.timeSlot << ";" << fieldData.fieldName << ";" << fieldData.price << endl;
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

void FieldManager::displayFields(const string& timeSlot) {
    Menu menu;
    menu.printSAN();
    loadFieldsFromFile("fields_details.txt");

    for (size_t i = 0; i < availableFields.get_size(); ++i) {
        string field = availableFields[i];
        int fieldPrice = 0;

        for (const auto& fieldData : fields) {
            if (fieldData.fieldName == field && fieldData.timeSlot == timeSlot) {
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
    displayFields(timeSlot);
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

// kiem tra san trong
bool FieldManager::isFieldAvailable(const string& timeSlot, const string& field) {
    Menu menu;
    string filePath = "TimeSlots/" + timeSlot + "/" + field + ".txt";

    ifstream file(filePath);
    if (!file.is_open()) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tERROR: Unable to open file " << filePath << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("STATUS: Available") != string::npos) {
            return true;
        }
    }
    return false;
}

// kiem tra nguoi dung nao da dat san
bool FieldManager::isFieldBookedByUser(const string& filePath, const string& username) {
    Menu menu;
    ifstream file(filePath);

    if (!file.is_open()) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tERROR: Unable to open file " << filePath << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("USERNAME: ") != string::npos) {
            string bookedUsername = line.substr(line.find(": ") + 2);
            if (bookedUsername == username) {
                return true;
            }
        }
    }

    return false;
}

// kiem tra dat san thanh cong
bool FieldManager::isBookField(const string& timeSlot, const string& field, const string& username, const string& customerName) {
    Menu menu;
    Account account;

    bool isAdmin = account.isAdminUser(username, "tk_quanly.txt");
    loadFieldsFromFile("fields_details.txt");
    string filePath = "TimeSlots/" + timeSlot + "/" + field + ".txt";

    if (!isFieldAvailable(timeSlot, field)) {
        system("cls");
        cout << "\t\t\t\t\t\t\t       THIS FIELD HAS ALREADY BEEN BOOKED. PLEASE CHECK ANOTHER FIELD!        " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }

    menu.displayBookingForm();

    string name, phone, address, paymentStatus, note;
    cout << "\033[13;72H" << field;

    if (isAdmin) {
        cout << "\033[14;71H";
        cin.ignore();
        getline(cin, name);
    }
    else {
        cout << "\033[14;71H" << customerName;
        cin.ignore();
        name = customerName;
    }
    
    cout << "\033[15;79H";
    getline(cin, phone);

    cout << "\033[16;74H";
    getline(cin, address);
    
    cout << "\033[17;100H";
    getline(cin, paymentStatus);
    
    cout << "\033[18;80H";
    getline(cin, note);

    int fieldPrice = 0;
    for (const auto& fieldData : fields) {
        if (fieldData.timeSlot == timeSlot && fieldData.fieldName == field) {
            fieldPrice = fieldData.price;
            break;
        }
    }

    ofstream file(filePath, ios::trunc);
    if (file.is_open()) {
        file << "FIELD: " << field << endl;
        file << "STATUS: Booked" << endl;
        file << "PRICE: " << fieldPrice << " VND" << endl;
        file << "USERNAME: " << username << endl;
        file << "CUSTOMER: " << name << endl;
        file << "PHONE NUMBER: " << phone << endl;
        file << "ADDRESS: " << address << endl;
        file << "PAYMENT DETAILS: " << paymentStatus << endl;
        file << "NOTE: " << note << endl;
        file.close();

        logAction(username, "Booked", field, timeSlot);

        system("cls");
        cout << "\t\t\t\t\t\t\t                    THE FIELD HAS BEEN SUCCESSFULLY BOOKED!                   " << endl;
        menu.printRETURN();
        cin.get();
        return true;
    } else {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tERROR: Unable to write to file " << filePath << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }
}

// kiem tra huy san thanh cong
bool FieldManager::isCancelBookField(const string& timeSlot, const string& field, const string& username) {
    Menu menu;
    Account account;
    FieldManager fieldManager;

    bool isAdmin = account.isAdminUser(username, "tk_quanly.txt");

    if (isFieldAvailable(timeSlot, field)) {
        system("cls");
        cout << "\t\t\t\t\t\t\t                THIS FIELD HAS NOT BEEN BOOKED. CANNOT CANCEL!                " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }

    if (!isAdmin && !isFieldBookedByUser("TimeSlots/" + timeSlot + "/" + field + ".txt", username)) {
        system("cls");
        cout << "\t\t\t\t\t\t\t                YOU DO NOT HAVE PERMISSION TO CANCEL THIS FIELD!              " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }

    string filePath = "TimeSlots/" + timeSlot + "/" + field + ".txt";
    loadFieldsFromFile("fields_details.txt");
    int fieldPrice = 0;
    for (const auto& fieldData : fields) {
        if (fieldData.fieldName == field) {
            fieldPrice = fieldData.price;
            break;
        }
    }

    ofstream file(filePath, ios::trunc);
    if (file.is_open()) {
        file << "FIELD: " << field << endl;
        file << "STATUS: Available" << endl;
        file << "PRICE: " << fieldPrice << " VND" << endl;
        file.close();

        logAction(username, "Canceled", field, timeSlot);

        system("cls");
        cout << "\t\t\t\t\t\t\t                   THE FIELD HAS BEEN SUCCESSFULLY CANCELED!                  " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return true;
    } else {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tERROR: Unable to write to file " << filePath << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }
}

// xem lich su dat san
void FieldManager::viewBookingHistory(const string& username) {
    Menu menu;
    Vector<string> timeSlots = readLinesFromFile("timeslots.txt");
    Vector<string> fields = readLinesFromFile("fields.txt");

    bool hasHistory = false;

    system("cls");
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t#                        BOOKING HISTORY                       #" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;

    for (size_t i = 0; i < timeSlots.get_size(); ++i) {
        string timeSlot = timeSlots[i];

        for (size_t j = 0; j < fields.get_size(); ++j) {
            string field = fields[j];
            string filePath = "TimeSlots/" + timeSlot + "/" + field + ".txt";

            ifstream file(filePath);
            if (file.is_open()) {
                string line;
                bool matchFound = false;
                while (getline(file, line)) {
                    if (line.find("USERNAME: " + username) != string::npos) {
                        matchFound = true;
                        break;
                    }
                }

                if (matchFound) {
                    hasHistory = true;
                    cout << "\n";
                    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                    cout << "\t\t\t\t\t\t\t\t|          " << setw(21) << left << timeSlot << " |            " << setw(17) << left << field << "|" << endl;
                    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;

                    file.clear();
                    file.seekg(0, ios::beg);
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
                    cout << "\t\t\t\t\t\t\t\t|   PRICE            :  " << setw(37) << left << price << "  |" << endl;
                    cout << "\t\t\t\t\t\t\t\t|   CUSTOMER         :  " << setw(37) << left << customer << "  |" << endl;
                    cout << "\t\t\t\t\t\t\t\t|   PHONE NUMBER     :  " << setw(37) << left << phone << "  |" << endl;
                    cout << "\t\t\t\t\t\t\t\t|   ADDRESS          :  " << setw(37) << left << address << "  |" << endl;
                    cout << "\t\t\t\t\t\t\t\t|   PAYMENT DETAILS  :  " << setw(37) << left << payment << "  |" << endl;
                    cout << "\t\t\t\t\t\t\t\t|   NOTE             :  " << setw(37) << left << note << "  |" << endl;
                    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                    cout << "\t\t\t\t\t\t\t________________________________________________________________________________" << endl;
                }
                file.close();
            }
        }
    }

    if (!hasHistory) {
        cout << "\n";
        cout << "\t\t\t\t\t\t\t                           NO BOOKING HISTORY FOUND!                          " << endl;
    }

    menu.printRETURN();
    cin.ignore();
    cin.get();
    system("cls");
}

// dat san
void FieldManager::bookField(const string& username, const string& customerName) {
    Menu menu;

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
                if (isBookField(timeSlot, field, username, customerName)) {
                    system("cls");
                    return;
                }
                else break;
            }
        }
    }
}

// huy san
void FieldManager::cancelBookField(const string& username) {
    Menu menu;

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

            if (isCancelBookField(timeSlot, field, username)) {
                system("cls");
                return;
            }
        }
    }
}

// kiem tra neu con san trong thi in ra
bool FieldManager::checkAvailableFields(const string& timeSlot) { 
    Menu menu;

    ifstream file("fields.txt");
    if (!file.is_open()) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tERROR: Unable to open fields data file!" << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return false;
    }
    file.close();
    
    Vector<string> fields = readLinesFromFile("fields.txt");
    bool hasAvailable = false;

    for (size_t i = 0; i < fields.get_size(); ++i) {
        if (isFieldAvailable(timeSlot, fields[i])) {
            if (!hasAvailable) {
                menu.printXEMSANTRONG();
                menu.printKHUNGGIO(timeSlot);
            }
            cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            cout << "\t\t\t\t\t\t\t\t|                            " << fields[i] << "                             |" << endl;
            cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            hasAvailable = true;
        }
    }

    return hasAvailable;
}

// xem san trong
void FieldManager::viewAvailableFields() {
    Menu menu;

    while (true) {
        system("cls"); 
        menu.printXEMSANTRONG();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) return;

        system("cls");
        if (!checkAvailableFields(timeSlot)) {
            cout << "\t\t\t\t\t\t\t                     NO AVAILABLE FIELDS IN THIS TIME SLOT!" << endl;
            menu.printRETURN();
        } else {
            menu.printRETURN();
        }
        cin.ignore();
        cin.get();
    }
}

// xem thong tin san
void FieldManager::viewFieldDetails() {
    Menu menu;
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
            file.close();

            system("cls");
            menu.printXEMSAN();
            menu.printKHUNGGIO(timeSlot);
            menu.printTENSAN(field);

            if (status == "Available") {
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t\t\t|                      FIELD   :   " << setw(27) << left << field << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                      STATUS  :   " << setw(27) << left << status << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|                      PRICE   :   " << setw(27) << left << price << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            } else if (status == "Booked") {
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t\t\t|       FIELD            :   " << setw(33) << left << field << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|       STATUS           :   " << setw(33) << left << status << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|       PRICE            :   " << setw(33) << left << price << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|       CUSTOMER         :   " << setw(33) << left << customer << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|       PHONE NUMBER     :   " << setw(33) << left << phone << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|       ADDRESS          :   " << setw(33) << left << address << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|       PAYMENT DETAILS  :   " << setw(33) << left << payment << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t|       NOTE             :   " << setw(33) << left << note << " |" << endl;
                cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
            }
            menu.printRETURN();
            cin.ignore();
            cin.get();
            break;
        }
    }
}

// xem tat ca gia san
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

// thay doi gia san
void FieldManager::changeFieldsPrice(const string& username) {
    Menu menu;
    FieldManager fieldManager;

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
                menu.printDOIGIA();
                menu.printKHUNGGIO(timeSlot);
                menu.printTENSAN(field);

                if (!isFieldAvailable(timeSlot, field)) {
                    system("cls");
                    cout << "\t\t\t\t\t\t\t\t     THIS FIELD IS NOT AVAILABLE. CANNOT CHANGE THE PRICE!" << endl;
                    menu.printRETURN();
                    cin.ignore();
                    cin.get();
                    break;
                }


                int newPrice;
                cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
                cout << "\t\t\t\t\t\t\t\t\t#     ENTER THE NEW PRICE FOR " << field << ":           #" << endl;
                cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
                cout << "\033[11;110H";

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
                    logAction(username, "Change Price", field, timeSlot);
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

// xem va in hoa don
void FieldManager::viewAndPrintInvoice() {
    Menu menu;

    while (true) {
        system("cls");
        menu.printINHOADON();
        string timeSlot = selectTimeSlot();
        if (timeSlot.empty()) return;

        while (true) {
            system("cls");
            menu.printINHOADON();
            menu.printKHUNGGIO(timeSlot);
            string field = selectField(timeSlot);
            if (field.empty()) break;
            printInvoice(timeSlot, field);
            menu.printRETURN();
            cin.ignore();
            cin.get();
        }
    }
}

// tim kiem hoa don
void FieldManager::searchAndDisplayInvoice() {
    Menu menu;
    string invoiceID;

    system("cls");
    menu.printTIMKIEMHOADON();
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t|   ENTER INVOICE ID (e.g., INV-001):                          |" << endl;
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\033[5;103H";
    cin >> invoiceID;

    string invoiceFilePath = "Invoices/" + invoiceID + ".txt";
    ifstream file(invoiceFilePath);

    if (!file.is_open()) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t\t\t\tINVOICE NOT FOUND!" << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return;
    }

    system("cls");
    cout << "\n\n";
    string line;
    while (getline(file, line)) {
        cout << "\t\t\t\t\t\t\t\t\t" << line << endl;
    }
    file.close();

    menu.printRETURN();
    cin.ignore();
    cin.get();
}

// hien thi hoa don ra man hinh va luu hoa don vao file
void FieldManager::printInvoice(const string& timeSlot, const string& field) {
    Menu menu;
    string filePath = "TimeSlots/" + timeSlot + "/" + field + ".txt";
    ifstream file(filePath);

    if (!file.is_open()) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\tERROR: Unable to open file " << filePath << endl;
        menu.printRETURN();
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
    file.close();

    time_t now = time(0);
    char* dt = ctime(&now);

    string invoiceID = generateInvoiceID();
    string invoiceFilePath = "Invoices/" + invoiceID + ".txt";
    ofstream outFile(invoiceFilePath);
    
    if (!outFile.is_open()) {
        cerr << "Unable to create invoice file!" << endl;
        return;
    }

    system("cls");
    cout << "\n\n";
    // in ra man hinh
    cout << "\t\t\t\t\t\t\t\t\t    ========================================" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t       SAN BONG BACH KHOA" << endl;
    cout << "\t\t\t\t\t\t\t\t\t    ========================================" << endl;
    cout << "\t\t\t\t\t\t\t\t\tAddr: 120 Nguyen Luong Bang, Q. Lien Chieu, Da Nang" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tTel: 09 6868 7777" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t  Service Hours: 15:30 - 23:30" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t    ------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tPAYMENT INVOICE" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t    ------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tTime: " << dt;
    cout << "\t\t\t\t\t\t\t\t\t\t      Invoice No: " << invoiceID << endl;
    cout << "\t\t\t\t\t\t\t\t\t    --------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tField: " << field << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tTime Slot: " << timeSlot << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tPrice: " << price << endl;
    cout << "\t\t\t\t\t\t\t\t\t    --------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tCustomer: " << customer << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tPhone: " << phone << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tAddress: " << address << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tNote: " << note << endl;
    int totalPrice = stoi(price);
    cout << "\t\t\t\t\t\t\t\t\t    --------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tTOTAL: " << totalPrice << " VND" << endl;
    cout << "\t\t\t\t\t\t\t\t\t    ========================================" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\tThank you for choosing our service!" << endl;

    // ghi vao file
    outFile << "    ========================================" << endl;
    outFile << "\t       SAN BONG BACH KHOA" << endl;
    outFile << "    ========================================" << endl;
    outFile << "Addr: 120 Nguyen Luong Bang, Q. Lien Chieu, Da Nang" << endl;
    outFile << "\t\tTel: 09 6868 7777" << endl;
    outFile << "\t  Service Hours: 15:30 - 23:30" << endl;
    outFile << "\t    ------------------------" << endl;
    outFile << "\t\tPAYMENT INVOICE" << endl;
    outFile << "\t    ------------------------" << endl;
    outFile << "\tTime: " << dt;
    outFile << "\t      Invoice No: " << invoiceID << endl;
    outFile << "     --------------------------------------" << endl;
    outFile << "\tField: " << field << endl;
    outFile << "\tTime Slot: " << timeSlot << endl;
    outFile << "\tPrice: " << price << endl;
    outFile << "     --------------------------------------" << endl;
    outFile << "\tCustomer: " << customer << endl;
    outFile << "\tPhone: " << phone << endl;
    outFile << "\tAddress: " << address << endl;
    outFile << "\tNote: " << note << endl;
    outFile << "     --------------------------------------" << endl;
    outFile << "\t\tTOTAL: " << totalPrice << " VND" << endl;
    outFile << "     ========================================" << endl;
    outFile << "\tThank you for choosing our service!" << endl;

    outFile.close();

    ofstream outFileReset(filePath, ios::trunc);
    if (outFileReset.is_open()) {
        outFileReset << "FIELD: " << field << endl;
        outFileReset << "STATUS: Available" << endl;
        outFileReset << "PRICE: " << price << endl;
        outFileReset.close();
    }
}

// tao ID hoa don
int FieldManager::invoiceCounter = 1;
string FieldManager::generateInvoiceID() {
    ostringstream invoiceID;
    invoiceID << "INV-" << setw(3) << setfill('0') << invoiceCounter++;

    return invoiceID.str();
}

// ghi lai hanh dong vao file log
void FieldManager::logAction(const string& username, const string& action, const string& field, const string& timeSlot) {
    time_t now = time(0);
    char* dt = ctime(&now);
    ofstream logFile("log.txt", ios::app);
    if (logFile.is_open()) {
        logFile << "Username: " << username << " | Action: " << action << " | Field: " << field 
                << " | TimeSlot: " << timeSlot << " | Time: " << dt << endl;
        logFile.close();
    } else {
        cerr << "Unable to open log file!" << endl;
    }
}