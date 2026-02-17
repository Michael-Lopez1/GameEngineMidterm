#pragma once

template<typename T>
class Singleton {
public:
    static T* GetInstance() {
        if (s_instance == nullptr) {
            s_instance = new T();
        }
        return s_instance;
    }

    static void DestroyInstance() {
        if (s_instance != nullptr) {
            delete s_instance;
            s_instance = nullptr;
        }
    }

protected:
    Singleton() {}
    virtual ~Singleton() {}

    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    static T* s_instance;
};

template<typename T>
T* Singleton<T>::s_instance = nullptr;
