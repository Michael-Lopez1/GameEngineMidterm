#pragma once

#include <vector>
#include <queue>

template<typename T>
class ObjectPool {
public:
    ObjectPool(size_t initialSize = 10) {
        for (size_t i = 0; i < initialSize; ++i) {
            T* obj = new T();
            m_availableObjects.push(obj);
            m_allObjects.push_back(obj);
        }
    }

    ~ObjectPool() {
        for (T* obj : m_allObjects) {
            delete obj;
        }
        m_allObjects.clear();
    }

    T* GetResource() {
        if (m_availableObjects.empty()) {
            // Grow pool if needed
            T* obj = new T();
            m_allObjects.push_back(obj);
            return obj;
        }

        T* obj = m_availableObjects.front();
        m_availableObjects.pop();
        return obj;
    }

    void ReturnResource(T* obj) {
        if (obj != nullptr) {
            m_availableObjects.push(obj);
        }
    }

    size_t GetTotalSize() const { return m_allObjects.size(); }
    size_t GetAvailableSize() const { return m_availableObjects.size(); }

private:
    std::vector<T*> m_allObjects;
    std::queue<T*> m_availableObjects;
};
