/**
 * 
 * @author:          kylin
 * @email:           kylin.du@outlook.com
 * @dateTime:        2019-04-09 Tue 09:48:18
 * @description:
 * @Copyright:       kylin.du
 * 
 */
#ifndef _ANY_H_
#define _ANY_H_

#include <type_traits>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "str.h"

namespace NetCore {
class any {
private:
    class valbase {
    public:
        virtual ~valbase(){}
        virtual valbase* clone() = 0;
        virtual const std::type_info& type() const noexcept = 0;
        //virtual operator type() = 0;
    };

    template <typename T>
    class value : public valbase {
    public:
        //typedef T value_type;
        value(const T& val) : _val(val){
            std::cout << "value(const T& val) : _val(val)" << std::endl;
        }
        value(T&& val) : _val(std::forward<T>(val)){
            std::cout << "value(T&& val) : _val(std::forward<T>(val))" << std::endl;
        }
        template <typename ... Args>
        value(Args&& ... args) : _val(std::forward<Args>(args)...) {
            std::cout << "value(Args&& ... args) : _val(std::forward<Args>(args)...)" << std::endl;
        }
        //operator T() {return _val;}
        // virtual operator type() override {return std::decltype(_val);}
        inline T& get(){return _val;}
    public:
        virtual const std::type_info& type() const noexcept {return typeid(T);}
        virtual valbase* clone() override {return new value(_val);}
    public:
        T _val;
    };
public:
    any() noexcept
        : _val(0) {}
    any(const any& other) : _val(other._val ? other._val->clone() : 0) {}
    any(any&& other) : _val(other._val) {other._val = 0;}
    
    any(CStr&& val) : _val(new value<typename std::decay<CStr>::type>(std::move(val))){}

    any(const char*& val) : _val(new value<CStr>(val)){
        std::cout << "any(const char*& val) : _val(new value<CStr>(val))" << std::endl;
    }
    any(char*&& val) : _val(new value<CStr>(std::forward<char*>(val))){
        std::cout << "any(char*&& val) : _val(new value<CStr>(std::forward(val)))" << std::endl;
    }
    any(const char*&& val) : _val(new value<CStr>(std::forward<const char*>(val))){
        std::cout << "ny(const char*&& val) : _val(new value<CStr>(std::forward<char*>(val)))" << std::endl;
    }
    // any(const unsigned char*& val) : _val(new value<CStr>(val)){}
    // any(unsigned char*&& val) : _val(new value<CStr>(std::move(val))){}

    template<typename T
        ,typename std::enable_if<!std::is_same<char*, typename std::decay<T>::type>::value >::type* = 0
        ,typename std::enable_if<!std::is_same<any, typename std::decay<T>::type>::value >::type* = 0>
    any(T&& val) : _val(new value<typename std::decay<T>::type>(std::forward<T>(val))){}

    template<typename T
        ,typename std::enable_if<!std::is_same<char*, typename std::decay<T>::type>::value >::type* = 0
        ,typename std::enable_if<!std::is_same<any, typename std::decay<T>::type>::value >::type* = 0>
    any(const T& val) : _val(new value<typename std::remove_cv<typename std::decay<const T>::type>::type>(val)){}
    
    ~any() noexcept {
        delete _val;
    }

    inline void swap(any&& other) {
        std::swap(_val,other._val);
    }

    // todo
    // inline bool operator==(any&& other) {
    //     return std::addressof(*this) == std::addressof(other) || _val == other._val || *_val == *(other._val) ;
    // }

    inline bool operator==(const char* val) {
        std::cout << "any : inline bool operator==(const char* val)" << std::endl;
        try {
            return (get<CStr>() == val);
        }catch (std::exception& e) {
            std::cout << e.what() <<std::endl;
            return false;
        }
        return false;
    }

    inline bool operator==(char*&& val) {
        std::cout << "any : inline bool operator==(char*&& val)" << std::endl;
        try {
            return (get<CStr>() == std::forward<char*>(val));
        }catch (std::exception& e) {
            std::cout << e.what() <<std::endl;
            return false;
        }
        return false;
    }

    template<typename T
        ,typename std::enable_if<!std::is_same<char*, typename std::decay<T>::type>::value >::type* = 0
        ,typename std::enable_if<!std::is_same<any, typename std::decay<T>::type>::value >::type* = 0>
    inline bool operator==(const T& val) {
        std::cout << "any : inline bool operator==(const T& val)" << std::endl;
        try {
            return (get<T>() == val);
        }catch (std::exception& e) {
            std::cout << e.what() <<std::endl;
            return false;
        }
        return false;
    }

    template<typename T
        ,typename std::enable_if<!std::is_same<char*, typename std::decay<T>::type>::value >::type* = 0
        ,typename std::enable_if<!std::is_same<any, typename std::decay<T>::type>::value >::type* = 0>
    inline bool operator==(T&& val) {
        std::cout << "any : inline bool operator==(T&& val)" << std::endl;
        try {
            return (get<T>() == std::forward<T>(val));
        }catch (std::exception& e) {
            std::cout << e.what() <<std::endl;
            return false;
        }
        return false;
    }
    


    inline any& operator=(const any& other) {
        std::cout << "any : inline any& operator=(const any& other)" << std::endl;
        delete _val;
        _val = other._val->clone();
        return *this;
    }

    inline any& operator=(any&& other) {
        std::cout << "any : inline any& operator=(any&& other)" << std::endl;
        std::swap(_val,other._val);
        return *this;
    }

    template<typename T
        ,typename std::enable_if<!std::is_same<char*, typename std::decay<T>::type>::value >::type* = 0
        ,typename std::enable_if<!std::is_same<any, typename std::decay<T>::type>::value >::type* = 0>
    inline any& operator=(const T& val) {
        std::cout << "any : inline any& operator=(const T& val)" << std::endl;
        delete _val;
        _val = new value<typename std::remove_cv<typename std::decay<const T>::type>::type>(val);
        return *this;
    }

    template<typename T
        ,typename std::enable_if<!std::is_same<char*, typename std::decay<T>::type>::value >::type* = 0
        ,typename std::enable_if<!std::is_same<any, typename std::decay<T>::type>::value >::type* = 0>
    inline any& operator=(T&& val) {
        std::cout << "any : inline any& operator=(T&& val)" << std::endl;
        //swap(any(std::move(val)));
        delete _val;
        _val = new value<typename std::decay<T>::type>(std::move(val));
        return *this;
    }

    inline any& operator=(const char*& val) {
        std::cout << "any : inline any& operator=(const char*& val)" << std::endl;
        delete _val;
        _val = new value<CStr>(val);
        return *this;
    }

    inline any& operator=(char*&& val) {
        std::cout << "any : inline any& operator=(char*&& val)" << std::endl;
        //swap(any(std::move(val)));
        delete _val;
        _val = new value<CStr>(std::move(val));
        return *this;
    }

    inline any& operator=(char*& val) {
        std::cout << "any : inline any& operator=(char*& val)" << std::endl;
        //swap(any(std::move(val)));
        delete _val;
        _val = new value<CStr>(val);
        return *this;
    }

    inline any& operator=(const char*&& val) {
        std::cout << "any : inline any& operator=(const char*&& val)" << std::endl;
        //swap(any(std::move(val)));
        delete _val;
        _val = new value<CStr>(std::forward<const char*>(val));
        return *this;
    }

    inline void clear() {
        delete _val;
        _val = 0;
    }
    inline bool empty() {
        return (_val == 0);
    }

    //operator type() {return (*_val) type;}
    const std::type_info& type() const noexcept {return _val ? _val->type() : typeid(void);}

    template<typename T>
    T& get() {
        // if (std::is_same<typename std::decay<T>::type, char*>::value) {
        //     if (typeid(CStr) != type()) {
        //         throw std::logic_error("type is not match!");
        //     }
        //     return static_cast<value<CStr>*>(_val)->_val.str();
        // }

        if (typeid(T) != type()) {
            throw std::logic_error("type is not match!");
        }
    
        return static_cast<value<typename std::decay<T>::type>*>(_val)->_val;
        //return static_cast<value<typename std::decay<value_type>::type>*>(_val)->get();
    }

    template<class T, class... Args>
    typename std::remove_cv<typename std::decay<const T>::type>::type& emplace(Args&&... args ) {
        auto val = new value<typename std::remove_cv<typename std::decay<const T>::type>::type>(std::forward<Args>(args)...);
        delete _val;
        _val = val;
        return val->_val;
    }

public:
    valbase* _val;
};

};


#endif //_ANY_H_