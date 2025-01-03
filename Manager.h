#pragma once

#include "Account.h"
#include <string>

class Manager : public Account {
public:
    Manager(const string& user, const string& pass, const string& n, const string& phone, const string& addr);
    void saveAccount(const string& filename) const override;
};
