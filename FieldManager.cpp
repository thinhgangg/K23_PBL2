#include "FieldManager.h"
#include "BookingManager.h"

using namespace std;

// chon gio
string FieldManager::selectTimeSlot() {
    Menu menu;
    menu.displayTimeSlots();
    int timeSlotChoice;
    cin >> timeSlotChoice;

    switch (timeSlotChoice) {
        case 1: return "15h30-16h30";
        case 2: return "16h30-17h30";
        case 3: return "17h30-18h30";
        case 4: return "18h30-19h30";
        case 5: return "19h30-20h30";
        case 6: return "20h30-21h30";
        case 7: return "21h30-22h30";
        case 8: return "22h30-23h30";
        case 9: return "23h30-00h30";
        case 0: 
            system("cls");
            return "";
        default:
            menu.displayError();
    }
}

// chon san
string FieldManager::selectField(const string& timeSlot) {
    Menu menu;
    menu.displayFieldList();
    int fieldChoice;
    cin >> fieldChoice;

    switch (fieldChoice) {
        case 1: return "San_A";
        case 2: return "San_B";
        case 3: return "San_C";
        case 4: return "San_D";
        case 5: return "San_E";
        case 0: 
            system("cls");
            return "";
        default:
            menu.displayError();
    }
}

// dat san
void FieldManager::bookField(const string& username) {
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

            if (booking.isBookField(timeSlot, field, username)) {
                system("cls");
                return;
            }
        }
    }
}

// huy san
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

// xem san trong
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
        if (!booking.displayFieldsForTimeSlot(timeSlot)) {
            cout << "\t\t\t\t\t                     NO AVAILABLE FIELDS IN THIS TIME SLOT!                   " << endl;
            menu.printRETURN();
        } else {
            menu.printRETURN();
        }
        cin.ignore();
        cin.get();
    }
}
