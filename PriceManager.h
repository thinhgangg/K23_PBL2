#pragma once
#define PRICEMANAGER_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
#include <iomanip>
#include "Vector.h" // Đừng quên bao gồm lớp Vector

// Cấu trúc lưu thông tin sân
struct SlotInfo {
    std::string fieldName; // Tên sân
    int price;             // Giá sân
};

// Cấu trúc lưu thông tin khung giờ
struct TimeSlot {
    std::string timeRange;                  // Khung giờ
    Vector<SlotInfo> slotInfos;             // Danh sách thông tin sân
};

// Lớp quản lý bảng giá sân
class PriceManager {
public:
    void displayPriceList(const std::string& filename = "price_list.txt"); // Hiển thị bảng giá
    void editPriceList(const std::string& filename = "price_list.txt");    // Chỉnh sửa bảng giá
private:
    void parsePriceList(const std::string& filename, Vector<TimeSlot>& data); // Đọc dữ liệu từ file
    void savePriceList(const std::string& filename, const Vector<TimeSlot>& data); // Ghi dữ liệu ra file
    void displayData(const Vector<TimeSlot>& data); // Hiển thị dữ liệu
    TimeSlot* findTimeSlot(Vector<TimeSlot>& data, const std::string& selectedTimeSlot); // Tìm khung giờ
    SlotInfo* findField(Vector<SlotInfo>& slotInfos, const std::string& fieldName); // Tìm sân
};