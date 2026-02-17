#pragma once

#include "StandardIncludes.h"
#include "StackAllocator.h"

struct ImageInfo {
    int Width;
    int Height;
    int BitsPerPixel;
    unsigned char* Data;
};

class Asset {
public:
    Asset() : m_data(nullptr), m_size(0) {}
    ~Asset() {
        if (m_data) {
            free(m_data);
        }
    }

    void SetData(void* data, size_t size) {
        m_data = data;
        m_size = size;
    }

    void* GetData() const { return m_data; }
    size_t GetSize() const { return m_size; }

private:
    void* m_data;
    size_t m_size;
};
