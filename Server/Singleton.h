#pragma once

template<typename T>
class Singleton {
public:
    static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value) {
        static T instance;
        return instance;
    }
    virtual ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator =(const Singleton&) = delete;
protected:
    //struct token {}; // helper class
    Singleton() noexcept = default;
};

// init static member
//Singleton* Singleton::instance = nullptr;