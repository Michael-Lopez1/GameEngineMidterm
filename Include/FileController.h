#pragma once

#include "StandardIncludes.h"
#include "Singleton.h"

class FileController : public Singleton<FileController> {
public:
    FileController() {}
    virtual ~FileController() {}

    bool ReadFile(const std::string& filepath, std::vector<unsigned char>& data) {
        std::ifstream file(filepath, std::ios::binary | std::ios::ate);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filepath << std::endl;
            return false;
        }

        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        data.resize(static_cast<size_t>(size));
        if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
            std::cerr << "Failed to read file: " << filepath << std::endl;
            return false;
        }

        return true;
    }

    bool WriteFile(const std::string& filepath, const void* data, size_t size) {
        std::ofstream file(filepath, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to create file: " << filepath << std::endl;
            return false;
        }

        file.write(reinterpret_cast<const char*>(data), size);
        return file.good();
    }
};
