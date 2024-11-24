#pragma once
#define FIELDMANAGER_H

#include "Vector.h"
#include "Menu.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

class FieldManager {
public:
    string selectTimeSlot();
    string selectField(const string& timeSlot);

    void bookField(const string& username);
    void cancelBookField(const string& username);
    void viewAvailableFields();
};
