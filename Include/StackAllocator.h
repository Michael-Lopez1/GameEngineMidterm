#pragma once

#include <cstddef>
#include <cstdlib>

class StackAllocator {
public:
    StackAllocator(size_t size) : m_size(size), m_used(0) {
        m_memory = malloc(size);
        m_current = m_memory;
    }

    ~StackAllocator() {
        if (m_memory) {
            free(m_memory);
        }
    }

    void* Allocate(size_t size) {
        if (m_used + size > m_size) {
            return nullptr; // Out of memory
        }

        void* result = m_current;
        m_current = static_cast<char*>(m_current) + size;
        m_used += size;
        return result;
    }

    void Clear() {
        m_used = 0;
        m_current = m_memory;
    }

    size_t GetUsed() const { return m_used; }
    size_t GetSize() const { return m_size; }

private:
    void* m_memory;
    void* m_current;
    size_t m_size;
    size_t m_used;
};
