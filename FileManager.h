#pragma once
#define FILEMANAGER_H

#include "Vector.h"
#include "Menu.h"
#include <fstream>

class FileManager {
public:
    Vector loadData(const string& filePath);
    Vector readAllLines(const string& filename);
    void writeAllLines(const string& filename, const Vector& lines);
};