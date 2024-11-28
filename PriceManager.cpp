#include "PriceManager.h"

using namespace std;

TimeSlot* PriceManager::findTimeSlot(Vector<TimeSlot>& data, const string& selectedTimeSlot) {
    for (size_t i = 0; i < data.get_size(); ++i) {
        if (data[i].timeRange == selectedTimeSlot) {
            return &data[i]; // Trả về con trỏ đến phần tử tìm thấy
        }
    }
    return nullptr; // Không tìm thấy
}

SlotInfo* PriceManager::findField(Vector<SlotInfo>& slotInfos, const string& fieldName) {
    for (size_t i = 0; i < slotInfos.get_size(); ++i) {
        if (slotInfos[i].fieldName == fieldName) {
            return &slotInfos[i]; // Trả về con trỏ đến sân tìm thấy
        }
    }
    return nullptr; // Không tìm thấy
}

// Hiển thị bảng giá
void PriceManager::displayPriceList(const std::string& filename) {
    Vector<TimeSlot> priceData;
    parsePriceList(filename, priceData); // Đọc dữ liệu từ file
    cout << "\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t##                      Price List                             ##" << endl;
    cout << "\t\t\t\t\t\t################################################################" << endl;
    displayData(priceData); // Hiển thị dữ liệu
    cout << "\t\t\t\t\t\t################################################################" << endl;
}

// Chỉnh sửa bảng giá
void PriceManager::editPriceList(const std::string& filename) {
    Vector<TimeSlot> priceData;
    parsePriceList(filename, priceData); // Đọc dữ liệu từ file

    // Hiển thị danh sách khung giờ
    cout << "\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t##                   Available Time Slots:                    ##" << endl;
    cout << "\t\t\t\t\t\t################################################################" << endl;
    for (size_t i = 0; i < priceData.get_size(); ++i) {
        cout << "\t\t\t\t\t\t##                      "<< i + 1 <<". "<< priceData[i].timeRange <<"                        ##"<< endl;
    }
    cout << "\t\t\t\t\t\t################################################################" << endl;

    // Chọn khung giờ để chỉnh sửa
    int timeSlotIndex;
    cout << "Select a time slot to edit (1-" << priceData.get_size() << "): ";
    while (true) {
        cin >> timeSlotIndex;
        if (cin.fail() || timeSlotIndex < 1 || timeSlotIndex > priceData.get_size()) {
            cin.clear(); // Xóa lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dòng
            cout << "Invalid selection. Please try again (1-" << priceData.get_size() << "): ";
        } else {
            break; // Nhập hợp lệ
        }
    }

    // Lưu khung giờ đã chọn vào biến selectedTimeSlot
    string selectedTimeSlot = priceData[timeSlotIndex - 1].timeRange;

    // Tìm khung giờ
    TimeSlot* timeSlot = findTimeSlot(priceData, selectedTimeSlot);
    if (timeSlot == nullptr) {
        cout << "Invalid time slot. Please try again." << endl;
        return;
    }

    // Hiển thị các sân trong khung giờ được chọn
    cout << "\t\t\t\t\t\t################################################################" << endl;
    cout << "\t\t\t\t\t\t##              Current Prices :     " << selectedTimeSlot << "              ##" << endl;
    cout << "\t\t\t\t\t\t################################################################" << endl;
    for (size_t i = 0; i < timeSlot->slotInfos.get_size(); ++i) {
        cout << "\t\t\t\t\t\t##           " << i + 1 << ". " << left << setw(10) << timeSlot->slotInfos[i].fieldName
             << " - Price: " << setw(10) << timeSlot->slotInfos[i].price << " VND" << "            ##" << endl;
    }
    cout << "\t\t\t\t\t\t################################################################" << endl;

    // Chọn sân để chỉnh sửa
    string selectedFieldName;
    cout << "Select a field to edit (Enter field name): ";
    cin >> selectedFieldName;

    // Tìm sân trong khung giờ
    SlotInfo* field = findField(timeSlot->slotInfos, selectedFieldName);
    if (field == nullptr) {
        cout << "Invalid field name. Please try again." << endl;
        return;
    }

    // Cập nhật giá sân
    int newPrice;
    cout << "Enter the new price for " << selectedFieldName << ": ";
    while (true) {
        cin >> newPrice;
        if (cin.fail() || newPrice < 0) {
            cin.clear(); // Xóa lỗi
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua dòng
            cout << "Invalid price. Please enter a positive number: ";
        } else {
            break; // Nhập hợp lệ
        }
    }

    field->price = newPrice;
    cout << "Price updated successfully!" << endl;

    // Ghi dữ liệu lại vào file
    savePriceList(filename, priceData);
}

// Đọc dữ liệu từ file
void PriceManager::parsePriceList(const std::string& filename, Vector<TimeSlot>& data) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    string line;
    TimeSlot currentTimeSlot;

    while (getline(file, line)) {
        // Kiểm tra nếu dòng là khung giờ (chứa ký tự '-')
        if (line.find('-') != string::npos) {
            // Nếu đã có dữ liệu của khung giờ trước đó, thêm vào danh sách
            if (!currentTimeSlot.timeRange.empty()) {
                data.push_back(currentTimeSlot);
                currentTimeSlot = TimeSlot(); // Reset khung giờ
            }
            currentTimeSlot.timeRange = line; // Lưu khung giờ mới
        } else if (!line.empty()) {
            // Xử lý dòng chứa thông tin sân và giá
            stringstream ss(line);
            SlotInfo slot;
            getline(ss, slot.fieldName, ','); // Lấy tên sân
            ss >> slot.price;                // Lấy giá sân
            currentTimeSlot.slotInfos.push_back(slot); // Thêm vào danh sách sân
        }
    }

    // Thêm khung giờ cuối cùng vào danh sách (nếu có)
    if (!currentTimeSlot.timeRange.empty()) {
        data.push_back(currentTimeSlot);
    }

    file.close();
}

// Ghi dữ liệu ra file
void PriceManager::savePriceList(const std::string& filename, const Vector<TimeSlot>& data) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    for (size_t i = 0; i < data.get_size(); ++i) {
        file << data[i].timeRange << endl; // Ghi khung giờ
        for (size_t j = 0; j < data[i].slotInfos.get_size(); ++j) {
            file << data[i].slotInfos[j].fieldName << "," << data[i].slotInfos[j].price << endl; // Ghi sân và giá
        }
    }

    file.close();
}

// Hiển thị dữ liệu
void PriceManager::displayData(const Vector<TimeSlot>& data) {
    cout << "Price List:" << endl;
    for (size_t i = 0; i < data.get_size(); ++i) {
        cout << "Time Slot: " << data[i].timeRange << endl;
        for (size_t j = 0; j < data[i].slotInfos.get_size(); ++j) {
            cout << "  Field: " << data[i].slotInfos[j].fieldName << " - Price: " << data[i].slotInfos[j].price << " VND" << endl;
        }
    }
}
