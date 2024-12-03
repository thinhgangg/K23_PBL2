#include "BookingManager.h"
using namespace std;

// kiem tra san trong
bool BookingManager::isFieldAvailable(const string& timeSlot, const string& field) {
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
bool BookingManager::isFieldBookedByUser(const string& filePath, const string& username) {
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
bool BookingManager::isBookField(const string& timeSlot, const string& field, const string& username, const string& customerName) {
    Menu menu;
    Account account;
    FieldManager fieldManager;

    bool isAdmin = account.isAdminUser(username, "tk_quanly.txt");
    fieldManager.loadFieldsFromFile("fields_details.txt");
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
    }
    
    cout << "\033[15;79H";
    getline(cin, phone);

    cout << "\033[16;74H";
    getline(cin, address);
    
    cout << "\033[17;108H";
    getline(cin, paymentStatus);
    
    cout << "\033[18;80H";
    getline(cin, note);

    int fieldPrice = 0;
    for (const auto& fieldData : fieldManager.fields) {
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
        file << "CUSTOMER: " << customerName << endl;
        file << "PHONE NUMBER: " << phone << endl;
        file << "ADDRESS: " << address << endl;
        file << "PAYMENT DETAILS: " << paymentStatus << endl;
        file << "NOTE: " << note << endl;
        file.close();

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
bool BookingManager::isCancelBookField(const string& timeSlot, const string& field, const string& username) {
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
    fieldManager.loadFieldsFromFile("fields_details.txt");
    int fieldPrice = 0;
    for (const auto& fieldData : fieldManager.fields) {
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
void BookingManager::viewBookingHistory(const string& username) {
    Menu menu;
    FileManager fileManager;
    Vector<string> timeSlots = fileManager.loadData("timeslots.txt");
    Vector<string> fields = fileManager.loadData("fields.txt");

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

// kiem tra neu con san trong thi in ra
bool BookingManager::checkAvailableFields(const string& timeSlot) { 
    Menu menu;
    FileManager fileManager;

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
    
    Vector<string> fields = fileManager.loadData("fields.txt");
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
