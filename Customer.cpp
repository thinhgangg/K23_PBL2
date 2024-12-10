#include "Customer.h"

Customer::Customer(const string& user, const string& pass, const string& n, const string& phone, const string& addr)
    : Account(user, pass, n, phone, addr) {}

void Customer::saveAccount(const string& filename) const {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        throw runtime_error("Error reading file: " + filename);
    }
    file << username << ";" << password << ";" << name << ";" << phoneNumber << ";" << address << endl;
    if (file.fail()) {
      throw runtime_error("Error writing to file: " + filename);
    }
}