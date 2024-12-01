#include "Menu.h"

void Menu::displayIntro() {
    system("cls");
    char ch;

    cout << "\t\t\t\t\t _____________________________________________________________________________________________________________________ \n";
    cout << "\t\t\t\t\t|                                       |                                                                             |\n";
    cout << "\t\t\t\t\t|     D                                 |                       MINISTRY OF EDUCATION AND TRAINING                    |\n";
    cout << "\t\t\t\t\t|                                       |          UNIVERSITY OF SCIENCE AND TECHNOLOGY-UNIVERSITY OF DA NANG         |\n";
    cout << "\t\t\t\t\t| B   A   C   H   K   H   O   A         |                              _________________                              |\n";
    cout << "\t\t\t\t\t|         ___________________________   |                                                                             |\n";
    cout << "\t\t\t\t\t|     N  |          ...              |  |                  LECTURER       : TRAN HO THUY TIEN                         |\n";
    cout << "\t\t\t\t\t|        |            ....           |  |                                                                             |\n";
    cout << "\t\t\t\t\t|     A  |             ......        |  |                  PROJECT        : PBL2 - FOOTBALL FIELD MANAGEMENT          |\n";
    cout << "\t\t\t\t\t|        |              .......      |  |                                                                             |\n";
    cout << "\t\t\t\t\t|     N  |              .........    |  |                  STUDENTS       : NGUYEN TRUNG KIEN                         |\n";
    cout << "\t\t\t\t\t|        |             ...........   |  |                                   MAI PHUC THINH                            |\n";
    cout << "\t\t\t\t\t|     G  |            .............  |  |                                                                             |\n";
    cout << "\t\t\t\t\t|        |          ...............  |  |                  SECTION CLASS  : 23.99A                                    |\n";
    cout << "\t\t\t\t\t|        |       ..................  |  |                                                                             |\n";
    cout << "\t\t\t\t\t|        |    ....................   |  |                  ACTIVITY CLASS : 23T_Nhat1                                 |\n";
    cout << "\t\t\t\t\t|        |  .....................    |  |                                                                             |\n";
    cout << "\t\t\t\t\t|        |  ...................      |  |                      Da Nang, Ngay 04 thang 01 nam 2025                     |\n";
    cout << "\t\t\t\t\t|        |___________________________|  |                                                                             |\n";
    cout << "\t\t\t\t\t|_______________________________________|_____________________________________________________________________________|\n"; 
    cout << "\n";
    cout << "\t\t\t\t\t\t\t\t\t\t\tPRESS ENTER TO START" << endl;
    do {
        ch = getch();
    } while (ch != 13);
    system("cls");
}

void Menu::displayLogo() {
    system("cls"); 
    ifstream logoFile("logo.txt");
    if (logoFile) {
        string line;
        while (getline(logoFile, line)) {
            cout << line << endl;
        }
    } else {
        cout << "LOGO FILE NOT FOUND!" << endl;
    }
}

void Menu::displayGoodbye() {
    system("cls"); 
    ifstream logoFile("goodbye.txt");
    if (logoFile) {
        string line;
        while (getline(logoFile, line)) {
            cout << line << endl;
        }
    } else {
        cout << "GOOBYE FILE NOT FOUND!" << endl;
    }
}

void Menu::homeMenu() {
    AccountManager accountManager;
    int choice;

    while (true) {
        displayLogo();
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##             FOOTBALL FIELD MANAGER APPLICATION             ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                        1. SIGN IN                          ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                        2. SIGN UP                          ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                        3. FORGOT PASSWORD?                 ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                        0. EXIT                             ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
        cin >> choice;

        switch (choice) {
            case 1:
                accountManager.login();
                break;
            case 2:
                accountManager.registerAccount("tk_khachhang.txt", "Customer");
                break;
            case 3:
                accountManager.resetPassword("tk_khachhang.txt");
                break;
            case 0:
                displayGoodbye();
                exit(0);
            default:
                printError();
        }
    }
}

void Menu::managerMenu(const string& username, const string& name) {
    AccountManager accountManager;
    FieldManager fieldManager;
    int choice;

    while (true) {
        system("cls"); 
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                    WELCOME, " << setw(30) << left << name << " ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                        MANAGER MENU                        ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 1. BOOK A FIELD                            ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 2. CANCEL A FIELD BOOKING                  ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 3. PRINT BILL & FREE FIELD                 ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 4. CUSTOMER DETAILS MANAGEMENT             ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 5. FIELD DETAILS MANAGEMENT                ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 6. REGISTER FOR AN ACCOUNT                 ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 7. RESET PASSWORD                          ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 8. ACCOUNT SETTINGS                        ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                 0. LOG OUT                                 ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
        cin >> choice;  

        switch (choice) {
            case 1:
                fieldManager.bookField(username, name);
                break;
            case 2:
                fieldManager.cancelBookField(username);
                break;
            case 3:
                // print bill
                break;
            case 4:
                customerDetailsMenu();
                break;
            case 5:
                fieldDetailsMenu();
                break;
            case 6:
                registrationMenu();
                break;
            case 7:
                resetPassMenu();
                break;
            case 8:
                accountSettingsMenu(username, true);
                break;
            case 0:
                return;
            default:
                printError();
        }
    }
}

void Menu::customerMenu(const string& username, const string& name) {
    int choice;
    FieldManager fieldManager;
    BookingManager booking;

    while (true) {
        system("cls"); 
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                    WELCOME, " << setw(30) << left << name << " ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                        CUSTOMER MENU                       ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                     1. BOOK A FIELD                        ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                     2. CANCEL A FIELD                      ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                     3. VIEW AVAILABLE FIELDS               ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                     4. VIEW BOOKING HISTORY                ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                     5. ACCOUNT SETTINGS                    ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                     0. LOG OUT                             ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
        cin >> choice;

        switch (choice) {
            case 1:
                fieldManager.bookField(username, name);
                break;
            case 2:
                fieldManager.cancelBookField(username);
                break;
            case 3:
                fieldManager.viewAvailableFields();
                break;
            case 4:
                booking.viewBookingHistory(username);
                break;
            case 5:
                accountSettingsMenu(username, false);
                break;
            case 0:
                return;
            default:
                printError();
        }
    }
}

void Menu::displaySignIn() {
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##                  SIGN IN                   ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       USERNAME:                            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       PASSWORD:                            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
}

void Menu::displaySignUp() {
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##                  SIGN UP                   ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       USERNAME:                            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       PASSWORD:                            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       NAME:                                ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       PHONE NUMBER:                        ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
}

void Menu::displayResetPass() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##               RESET PASSWORD               ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       USERNAME:                            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       PHONE NUMBER:                        ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
}

void Menu::displayChangePass() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##              CHANGE PASSWORD               ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       CURRENT PASSWORD:                    ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
}

void Menu::displayChangePhone() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##             CHANGE PHONE NUMBER            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       PHONE NUMBER:                        ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       NEW PHONE NUMBER:                    ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
}

void Menu::displaySearchCustomer() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##               SEARCH CUSTOMER              ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##       PHONE NUMBER:                        ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
}

void Menu::printRETURN() {
    cout << "\n";
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t##          PRESS ENTER TO RETURN...          ##" << endl;
    cout << "\t\t\t\t\t\t\t\t\t################################################" << endl;
}

void Menu::printError() {
    system("cls");
    cout << "\t\t\t\t\t\t\t\t\t\t\tINVALID CHOICE!                 " << endl;
    printRETURN();
    cin.ignore();
    cin.get();
    system("cls");
}

void Menu::registrationMenu() {
    system("cls"); 
    AccountManager accountmanager;
    int registrationChoice;

    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                   REGISTER FOR AN ACCOUNT                  ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                1. REGISTER A MANAGER ACCOUNT               ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                2. REGISTER A CUSTOMER ACCOUNT              ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                0. GO BACK                                  ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
    cin >> registrationChoice;

    switch (registrationChoice) {
        case 1:
            accountmanager.registerAccount("tk_quanly.txt", "Manager");
            break;
        case 2:
            accountmanager.registerAccount("tk_khachhang.txt", "Customer");
            break;
        case 0:
            system("cls");
            break;
        default:
            printError();
    }
}

void Menu::resetPassMenu() {
    system("cls"); 
    AccountManager accountManager;
    int resetChoice;

    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                       RESET PASSWORD                       ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##              1. RESET MANAGER ACCOUNT PASSWORD             ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##              2. RESET CUSTOMER ACCOUNT PASSWORD            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##              0. GO BACK                                    ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
    cin >> resetChoice;

    switch (resetChoice) {
        case 1:
            accountManager.resetPassword("tk_quanly.txt");
            break;
        case 2:
            accountManager.resetPassword("tk_khachhang.txt");
            break;
        case 0:
            system("cls");
            break;
        default:
            printError();
    }
}

// void Menu::priceManagerMenu() {
//     system("cls"); 
//     int choice;
//     cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
//     cout << "\t\t\t\t\t\t\t\t##                   FIELD PRICE MANAGEMENT                   ##" << endl;
//     cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
//     cout << "\t\t\t\t\t\t\t\t##                  1. VIEW ALL FIELD PRICES                  ##" << endl;
//     cout << "\t\t\t\t\t\t\t\t##                  2. UPDATE FIELD PRICES                    ##" << endl;
//     cout << "\t\t\t\t\t\t\t\t##                  0. GO BACK                                ##" << endl;
//     cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
//     cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
//     cin >> choice;
//     switch (choice) {
//         case 1:
//             cout << "ok" << endl;
//             priceManager.displayPriceList(filename);
//             break;
//         case 2:
//             cout << "ok" << endl;
//             priceManager.editPriceList(filename);
//             break;
//         case 0:
//             system("cls");
//             break;
//         default:
//             printError();
//     }
// }

void Menu::printDATSAN() {
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                        BOOK A FIELD                        ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
}

void Menu::printHUYSAN() {
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                       CANCEL A FIELD                       ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
}

void Menu::printKHUNGGIO(const string& timeSlot) {
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                        "<<timeSlot<<"                         ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
}

void Menu::printTENSAN(const string& field) {
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                           "<<field<<"                            ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
}

void Menu::printGIO() {
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t|                          TIME SLOTS                          |" << endl;
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
}

void Menu::printSAN() {
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t\t|                            FIELDS                            |" << endl;
    cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
}

void Menu::printXEMSAN() {
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                     VIEW FIELD DETAILS                     ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
}

void Menu::printXEMSANTRONG() {
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                   VIEW AVAILABLE FIELDS                    ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
}

void Menu::displayBookingForm() {
    cout << "\t\t\t\t\t\t\t--------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t|                               BOOKING DETAILS                                |" << endl;
    cout << "\t\t\t\t\t\t\t--------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t\t|       FIELD:                                                                 |" << endl;
    cout << "\t\t\t\t\t\t\t|       NAME:                                                                  |" << endl;
    cout << "\t\t\t\t\t\t\t|       PHONE NUMBER:                                                          |" << endl;
    cout << "\t\t\t\t\t\t\t|       PAYMENT DETAILS (BY CASH / BANK TRANSFER):                             |" << endl;
    cout << "\t\t\t\t\t\t\t|       NOTE (IF ANY):                                                         |" << endl;
    cout << "\t\t\t\t\t\t\t--------------------------------------------------------------------------------" << endl;
}

void Menu::customerInfoMenu(const string& username, const string& name, const string& phone) {
    FieldManager fieldManager;
    AccountManager accountManager;
    BookingManager booking;

    int choice;
    while (true) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                    CUSTOMER INFORMATION                    ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;

        cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\t\t|                    CUSTOMER: " << setw(31) << left << name << " |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                    USERNAME: " << setw(31) << left << username << " |" << endl;
        cout << "\t\t\t\t\t\t\t\t|                    PHONE: " << setw(34) << left << phone << " |" << endl;
        cout << "\t\t\t\t\t\t\t\t----------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                   1. VIEW BOOKING HISTORY                  ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                   2. RESET PASSWORD                        ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                   3. DELETE ACCOUNT                        ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                   0. GO BACK                               ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
        cin >> choice;

        switch (choice) {
            case 1:
                booking.viewBookingHistory(username);
                break;
            case 2:
                accountManager.resetPassword("tk_khachhang.txt");
                break;
            case 3:
                accountManager.deleteAccount("tk_khachhang.txt", username);
                return;
            case 0:
                system("cls");
                return;
            default:
                printError();
        }
    }
}

void Menu::accountSettingsMenu(const string& username, bool isAdmin) {
    AccountManager accountManager;
    UserManager userManager;
    FileManager fileManager;

    string fileName = isAdmin ? "tk_quanly.txt" : "tk_khachhang.txt";
    int choice;
    while (true) {
        system("cls");
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                   ACCOUNT SETTINGS MENU                    ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t##                1. CHANGE PHONE NUMBER                      ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                2. CHANGE PASSWORD                          ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                3. DELETE ACCOUNT                           ##" << endl;
        cout << "\t\t\t\t\t\t\t\t##                0. GO BACK                                  ##" << endl;
        cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
        cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                accountManager.changePhoneNumber(fileName, username);
                break;
            case 2: 
                accountManager.changePassword(fileName, username);
                break;
            case 3: {
                while (true) {
                    char confirmChoice;
                    system("cls");
                    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
                    cout << "\t\t\t\t\t\t\t\t##                       DELETE ACCOUNT                       ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
                    cout << "\t\t\t\t\t\t\t\t##       ARE YOU SURE YOU WANT TO DELETE YOUR ACCOUNT?        ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t##                  THIS CANNOT BE UNDONE!!!                  ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
                    cout << "\t\t\t\t\t\t\t\t##                           1. YES                           ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t##                           2. NO                            ##" << endl;
                    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
                    cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
                    cin >> confirmChoice;

                    if (confirmChoice == '1') {
                        accountManager.deleteAccount(fileName, username);
                        displayGoodbye();
                        exit(0);
                    } else if (confirmChoice == '2') {
                        system("cls");
                        break;
                    } else {
                        printError();
                    }
                }
                break;
            }
            case 0:
                system("cls");
                return;
            default:
                printError();
        }
    }
}

void Menu::customerDetailsMenu() {
    system("cls"); 
    AccountManager accountManager;
    int choice;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                 CUSTOMER DETAILS MANAGEMENT                ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    1. SEARCH CUSTOMER                      ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    2. VIEW CUSTOMER LIST                   ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    0. GO BACK                              ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
    cin >> choice;
    switch (choice) {
        case 1:
            accountManager.searchCustomer();
            break;
        case 2:
            accountManager.viewCustomerList();
            break;
        case 0:
            system("cls");
            break;
        default:
            printError();
    }
}

void Menu::fieldDetailsMenu() {
    system("cls"); 
    FieldManager fieldManager;
    fieldManager.loadFieldsFromFile("fields_details.txt");
    int choice;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                  FIELD DETAILS MANAGEMENT                  ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    1. VIEW FIELD DETAILS                   ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    2. VIEW AVAILABLE FIELDS                ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    3. VIEW ALL FIELDS PRICE                ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    4. CHANGE FIELDS PRICE                  ##" << endl;
    cout << "\t\t\t\t\t\t\t\t##                    0. GO BACK                              ##" << endl;
    cout << "\t\t\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\tYOUR CHOICE: ";
    cin >> choice;
    switch (choice) {
        case 1:
            fieldManager.viewFieldDetails();
            break;
        case 2:
            fieldManager.viewAvailableFields();
            break;
        case 3:
            fieldManager.viewAllFieldsPrice();
            break;
        case 4:
            fieldManager.changeFieldsPrice();
            break;
        case 0:
            system("cls");
            break;
        default:
            printError();
    }
}