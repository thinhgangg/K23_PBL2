#include "AccountManager.h"

using namespace std;

// doc tat ca cac dong tu file vao vector
Vector<string> AccountManager::readAllLines(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        system("cls");
        throw runtime_error("Unable to open file " + filename);
    }

    Vector<string> lines;
    string line;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    if (file.bad()) {
        system("cls");
        throw runtime_error("Unable to read file: " + filename);
    }

    file.close();
    return lines;
}

// ghi tat ca cac dong tu vector vao file
void AccountManager::writeAllLines(const string& filename, const Vector<string>& lines) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        system("cls");
        throw runtime_error("Unable to open file " + filename);
    }

    for (size_t i = 0; i < lines.get_size(); i++) {
        file << lines[i] << endl;
        if (file.fail()) {
            system("cls");
            throw runtime_error("Error writing to file: " + filename);
        }
    }
    file.close();
}

// dang nhap
void AccountManager::login() {
    system("cls");

    Account account;
    Menu menu;
    menu.displaySignIn();

    string user, pass, name;
    cout << "\033[4;92H";
    cin >> user;

    cout << "\033[6;92H";
    pass = inputPassword();

    if (account.getUserInfo("tk_quanly.txt", user, pass, name)) {
        menu.managerMenu(user, name);
    } 
    else if (account.getUserInfo("tk_khachhang.txt", user, pass, name)) {
        menu.customerMenu(user, name);
    } else {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t\t       USERNAME OR PASSWORD IS INCORRECT!       " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
    }
}

// dang ky tai khoan
void AccountManager::registerAccount(const string& filename, const string& accountType) {
    system("cls");

    Menu menu;
    menu.displaySignUp();

    string user, pass, name, phone, addr;

    // nhap username
    while (true) {
        cout << "\033[4;92H";
        cin >> user;

        if (!isValidUsername(user)) {
            cout << ERROR_INVALID_USERNAME << endl;
            cout << "\033[4;92H                           " << endl;
        } else if (isUsernameTaken(user)) {
            cout << "\033[14;50H                                                                                                    " << endl;
            cout << ERROR_EXISTS_USERNAME << endl;
            cout << "\033[4;92H                           " << endl;
        } else {
            cout << "\033[14;50H                                                                                                    " << endl;
            break;
        }
    }


    // nhap password
    while (true) {
        cout << "\033[6;92H";
        pass = inputPassword();

        if (!isValidPassword(pass)) {
            cout << ERROR_INVALID_PASSWORD << endl;
            cout << "\033[6;92H                           " << endl;
        } else {
            cout << "\033[14;50H                                                                                                    " << endl;
            break;
        }
    }


    // nhap name
    while (true) {
        cout << "\033[8;88H";
        cin.ignore();
        getline(cin, name);

        if (!isValidName(name)) {
            cout << ERROR_INVALID_NAME << endl;
            cout << "\033[8;88H                               " << endl;
        } else {
            cout << "\033[14;50H                                                                                                    " << endl;
            break;
        }
    }

    // nhap phone number
    while (true) {
        cout << "\033[10;96H";
        cin >> phone;

        if (!isValidPhone(phone)) {
            cout << ERROR_INVALID_PHONENUMBER << endl;
            cout << "\033[10;96H                       ";
        } else if (isPhoneNumberTaken(phone)) {
            cout << "\033[14;50H                                                                                                    " << endl;
            cout << ERROR_EXISTS_PHONENUMBER << endl;
            cout << "\033[10;96H                       ";
        } else {
            cout << "\033[14;50H                                                                                                    " << endl;
            break;
        }
    }

    // nhap dia chi
    cout << "\033[12;91H";
    cin.ignore();
    getline(cin, addr);

    if (accountType == "Customer") {
        Customer newCustomer(user, pass, name, phone, addr);
        newCustomer.saveAccount(filename);
    } else if (accountType == "Manager") {
        Manager newManager(user, pass, name, phone, addr);
        newManager.saveAccount(filename);
    }

    system("cls");
    cout << "\t\t\t\t\t\t\t\t\t            REGISTRATION SUCCESSFUL!            " << endl;
    menu.printRETURN();
    cin.get();
}

// dat lai mat khau
void AccountManager::resetPassword(const string& filename) {
    system("cls");

    Menu menu;

    while (true) {
        string username, phoneNum, newPassword, confirmPassword;

        menu.displayResetPass();

        cout << "\033[4;92H";
        cin >> username;
        cout << "\033[6;96H";
        cin >> phoneNum;

        // doc danh sach tai khoan
        Vector<string> lines = readAllLines(filename);
        bool accountFound = false;

        for (size_t i = 0; i < lines.get_size(); i++) {
            stringstream ss(lines[i]);
            string u, p, name, phone, addr;
            getline(ss, u, ';');
            getline(ss, p, ';');
            getline(ss, name, ';');
            getline(ss, phone, ';');
            getline(ss, addr, ';');

            // neu tim thay tai khoan
            if (u == username && phone == phoneNum) {
                while (true) {
                    cout << "\033[8;00H";
                    cout << "\t\t\t\t\t\t\t\t\t##       NEW PASSWORD:                        ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
                    cout << "\033[8;96H";
                    newPassword = inputPassword();

                    // kiem tra password hop le
                    if (!isValidPassword(newPassword)) {
                        system("cls");
                        cout << "\t\t\t\t\t\t\t\t\t  PASSWORD MUST BE AT LEAST 6 CHARACTERS LONG!  " << endl;
                        menu.printRETURN();
                        cin.ignore();
                        cin.get();
                        return;
                    } else {
                        cout << "\n";
                        cout << "\t\t\t\t\t\t\t\t\t##       CONFIRM NEW PASSWORD:                ##" << endl;
                        cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
                        cout << "\033[10;104H";
                        confirmPassword = inputPassword();

                        // confirm password
                        if (newPassword != confirmPassword) {
                            system("cls");
                            cout << "\t\t\t\t\t\t\t\t\t            PASSWORDS DO NOT MATCH!             " << endl;
                            menu.printRETURN();
                            cin.ignore();
                            cin.get();
                            return;
                        } else {
                            stringstream newLine;
                            newLine << u << ";" << newPassword << ";" << name << ";" << phone;
                            lines[i] = newLine.str();
                            accountFound = true;
                            break;
                        }
                    }
                }
                if (accountFound) break;
            }
        }

        if (accountFound) {
            writeAllLines(filename, lines);
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t         PASSWORD UPDATED SUCCESSFULLY!         " << endl;
            menu.printRETURN();
            cin.ignore();
            cin.get();
            return;
        } else {
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t          THE ACCOUNT DOES NOT EXIST!           " << endl;
            menu.printRETURN();
            cin.ignore();
            cin.get();
            return;
        }
    }
}

// doi mat khau
void AccountManager::changePassword(const string& filename, const string& username) {
    system("cls");

    Menu menu;

    while (true) {
        string currentPassword, newPassword, confirmPassword;

        menu.displayChangePass();
        cout << "\033[4;100H";
        currentPassword = inputPassword();

        Vector<string> lines = readAllLines(filename);
        bool accountFound = false;

        for (size_t i = 0; i < lines.get_size(); i++) {
            stringstream ss(lines[i]);
            string u, p, name, phone, addr;
            getline(ss, u, ';');
            getline(ss, p, ';');
            getline(ss, name, ';');
            getline(ss, phone, ';');
            getline(ss, addr, ';');

            if (u == username && p == currentPassword) {
                while (true) {
                    cout << "\033[6;00H";
                    cout << "\t\t\t\t\t\t\t\t\t##       NEW PASSWORD:                        ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
                    cout << "\033[6;96H";
                    newPassword = inputPassword();

                    if (!isValidPassword(newPassword)) {
                        system("cls");
                        cout << "\t\t\t\t\t\t\t\t\t  PASSWORD MUST BE AT LEAST 6 CHARACTERS LONG!  " << endl;
                        menu.printRETURN();
                        cin.ignore();
                        cin.get();
                        return;
                    } else {
                        cout << "\n";
                        cout << "\t\t\t\t\t\t\t\t\t##       CONFIRM NEW PASSWORD:                ##" << endl;
                        cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
                        cout << "\033[8;104H";
                        confirmPassword = inputPassword();

                        // confirm password
                        if (newPassword != confirmPassword) {
                            system("cls");
                            cout << "\t\t\t\t\t\t\t\t\t            PASSWORDS DO NOT MATCH!             " << endl;
                            menu.printRETURN();
                            cin.ignore();
                            cin.get();
                            return;
                        } else {
                            stringstream newLine;
                            newLine << u << ";" << newPassword << ";" << name << ";" << phone;
                            lines[i] = newLine.str();
                            accountFound = true;
                            break;
                        }
                    }
                }
                if (accountFound) break;
            }
        }
        if (accountFound) {
            writeAllLines(filename, lines);
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t         PASSWORD UPDATED SUCCESSFULLY!         " << endl;
            menu.printRETURN();
            cin.ignore();
            cin.get();
            system("cls");
            return;
        } else {
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t         CURRENT PASSWORD IS INCORRECT!         " << endl;
            menu.printRETURN();
            cin.ignore();
            cin.get();
            system("cls");
            return;
        }
    }
}

// thay doi so dien thoai
void AccountManager::changePhoneNumber(const string& filename, const string& username) {
    system("cls");

    Menu menu;

    while (true) {
        string newPhone, password;

        Vector<string> lines = readAllLines(filename);
        bool accountFound = false;

        for (size_t i = 0; i < lines.get_size(); i++) {
            stringstream ss(lines[i]);
            string u, p, name, phone, addr;
            getline(ss, u, ';');
            getline(ss, p, ';');
            getline(ss, name, ';');
            getline(ss, phone, ';');
            getline(ss, addr, ';');

            if (u == username) {
                while (true) {
                    system("cls");
                    menu.displayChangePhone();
                    cout << "\033[4;96H" << phone;
                    cout << "\033[6;100H";
                    cin >> newPhone;

                    if (newPhone == phone) {
                        system("cls");
                        cout << "\t\t\t\t\t\t\t\t\tNEW PHONE NUMBER CANNOT BE THE SAME AS THE OLD ONE!" << endl;
                        Menu menu;
                        menu.printRETURN();
                        cin.ignore();
                        cin.get();
                        return;
                    }

                    if (!isValidPhone(newPhone)) {
                        system("cls");
                        cout << "\t\t\t\t\t\t\t\t\t     INVALID PHONE NUMBER! PLEASE TRY AGAIN!    " << endl;
                        Menu menu;
                        menu.printRETURN();
                        cin.ignore();
                        cin.get();
                        return;
                    } else if (isPhoneNumberTaken(newPhone)) {
                        system("cls");
                        cout << "\t\t\t\t\t\t\t\t\t      THIS PHONE NUMBER ALREADY REGISTERED!     " << endl;
                        Menu menu;
                        menu.printRETURN();
                        cin.ignore();
                        cin.get();
                        return;
                    }

                    cout << "\033[8;00H";
                    cout << "\t\t\t\t\t\t\t\t\t##       VERIFY YOUR PASSWORD:                ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
                    cout << "\033[8;104H";
                    password = inputPassword();

                    if (password == p) {
                        stringstream newLine;
                        newLine << u << ";" << p << ";" << name << ";" << newPhone;
                        lines[i] = newLine.str();
                        accountFound = true;

                        writeAllLines(filename, lines);

                        system("cls");
                        cout << "\t\t\t\t\t\t\t\t\t       PHONE NUMBER UPDATED SUCCESSFULLY!       " << endl;
                        Menu menu;
                        menu.printRETURN();
                        cin.ignore();
                        cin.get();
                        return;
                    } else {
                        system("cls");
                        cout << "\t\t\t\t\t\t\t\t\t  INCORRECT PASSWORD! PHONE NUMBER NOT UPDATED! " << endl;
                        Menu menu;
                        menu.printRETURN();
                        cin.ignore();
                        cin.get();
                        return;
                    }
                }
            }
        }

        if (!accountFound) {
            system("cls");
            cout << "\t\t\t\t\t\t\t\t\t          THE ACCOUNT DOES NOT EXIST!           " << endl;
            Menu menu;
            menu.printRETURN();
            cin.ignore();
            cin.get();
            return;
        }
    }
}

// xoa tai khoan
void AccountManager::deleteAccount(const string& filename, const string& username) {
    Menu menu;

    if (isdeleteAccount(filename, username)) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t                 ACCOUNT DELETED SUCCESSFULLY!                " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return;
    } else {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t                  UNABLE TO DELETE ACCOUNT!                   " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
    }
}

// tim kiem khach hang
void AccountManager::searchCustomer() {
    system("cls");

    Menu menu;

    string phone;
    bool customerFound = false;

    menu.displaySearchCustomer();
    cout << "\033[4;96H";
    cin >> phone;

    Vector<string> lines = readAllLines("tk_khachhang.txt");

    for (size_t i = 0; i < lines.get_size(); ++i) {
        stringstream ss(lines[i]);
        string username, password, name, phoneNum, address;
        getline(ss, username, ';');
        getline(ss, password, ';');
        getline(ss, name, ';');
        getline(ss, phoneNum, ';');
        getline(ss, address, ';');

        if (phoneNum == phone) {
            menu.customerOptionMenu(username, name, phone, address);
            customerFound = true;
            break;
        }
    }

    if (!customerFound) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t\t              CUSTOMER NOT FOUND!               " << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
    }
}

// xem danh sach khach hang
void AccountManager::viewCustomerList() {
    Menu menu;
    system("cls");

    ifstream file("tk_khachhang.txt");
    if (!file.is_open()) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t\t\tERROR: Unable to open file" << endl;
        menu.printRETURN();
        cin.ignore();
        cin.get();
        return;
    }

    string line, username, password, name, phone, address;
    Vector<string> customers;

    while (getline(file, line)) {
        customers.push_back(line);
    }
    file.close();

    while (true) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                       CUSTOMER LIST                        ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;

        cout << "\t\t\t\t\t================================================================================================================" << endl;
        cout << "\t\t\t\t\t|   No  |          CUSTOMER          |      USERNAME      |     PHONE      |              ADDRESS              |" << endl;
        cout << "\t\t\t\t\t================================================================================================================" << endl;

        for (size_t i = 0; i < customers.get_size(); ++i) {
            stringstream ss(customers[i]);
            getline(ss, username, ';');
            getline(ss, password, ';');
            getline(ss, name, ';');
            getline(ss, phone, ';');
            getline(ss, address, ';');

            cout << "\t\t\t\t\t|   " << setw(3) << left << i + 1 
                 << " |   " << setw(24) << left << name 
                 << " |   " << setw(16) << left << username 
                 << " |   " << setw(12) << phone 
                 << " |   " << setw(31) << address
                 << " |" << endl;
            cout << "\t\t\t\t\t================================================================================================================" << endl;
        }
        cout << "\t\t\t\t\t\t\t\t================================================================" << endl;
        cout << "\t\t\t\t\t\t\t\t|      CHOOSE A CUSTOMER BY INDEX (1-" << customers.get_size() << ") OR 0 TO GO BACK:      |" << endl;
        cout << "\t\t\t\t\t\t\t\t================================================================" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            system("cls");
            return;
        } else if (choice > 0 && choice <= customers.get_size()) {
            stringstream ss(customers[choice - 1]);
            getline(ss, username, ';');
            getline(ss, password, ';');
            getline(ss, name, ';');
            getline(ss, phone, ';');
            getline(ss, address, ';');

            menu.customerOptionMenu(username, name, phone, address);
        } else {
            menu.printError();
        }
    }
}

// kiem tra username hop le
bool AccountManager::isValidUsername(const string& username) {
    if (username.length() < 5) {
        return false;
    }
    for (char ch : username) {
        if (!islower(ch) && !isdigit(ch) && ch != '_') {
            return false;
        }
    }
    return true;
}

// kiem tra username da ton tai
bool AccountManager::isUsernameTaken(const string& user) {
    return Account::accountExists("tk_khachhang.txt", user) || Account::accountExists("tk_quanly.txt", user);
}

// kiem tra password hop le
bool AccountManager::isValidPassword(const string& password) {
    return password.length() >= 6;
}

// kiem tra name hop le
bool AccountManager::isValidName(const string& name) {
    for (char c : name) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return !name.empty();
}

// kiem tra phone number hop le
bool AccountManager::isValidPhone(const string& phone) {
    if (phone.length() != 10) {
        return false;
    }
    for (char c : phone) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// kiem tra phone number da duoc su dung
bool AccountManager::isPhoneNumberTaken(const string& phone) {
    Vector<string> accounts = readAllLines("tk_khachhang.txt");
    for (size_t i = 0; i < accounts.get_size(); ++i) {
        stringstream ss(accounts[i]);
        string username, password, name, storedPhone;
        getline(ss, username, ';');
        getline(ss, password, ';');
        getline(ss, name, ';');
        getline(ss, storedPhone, ';');

        if (storedPhone == phone) {
            return true;
        }
    }
    return false;
}

// nhap mat khau hien thi *
string AccountManager::inputPassword() {
    string pass = "";
    char ch;
    while (true) {
        ch = _getch();
        if (ch == '\r') {
            cout << endl;
            break;
        } else if (ch == '\b') {
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else {
            pass += ch;
            cout << "*";
        }
    }
    return pass;
}

// kiem tra xoa tai khoan thanh cong
bool AccountManager::isdeleteAccount(const string& filename, const string& username) {
    Vector<string> lines = readAllLines(filename);
    bool accountFound = false;

    for (size_t i = 0; i < lines.get_size(); ++i) {
        stringstream ss(lines[i]);
        string u, p, name, phone;

        getline(ss, u, ';');
        getline(ss, p, ';');
        getline(ss, name, ';');
        getline(ss, phone, ';');

        if (u == username) {
            lines.erase(i);
            accountFound = true;
            break;
        }
    }

    if (accountFound) {
        writeAllLines(filename, lines);
        return true;
    }

    return false;
}