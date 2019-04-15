/**
 * 
 * @author:          kylin
 * @email:           kylin.du@outlook.com
 * @dateTime:        2019-04-09 Tue 09:48:18
 * @description:     a simple string class
 * @Copyright:       kylin.du
 * 
 */

#ifndef _STR_H_
#define _STR_H_

#include <string.h>
#include <stdlib.h>
#include <utility>
#include <stdio.h>
#include "base.h"

namespace NetCore {

class CStr {
public:
    CStr() {
        init();
    }
    CStr(const CStr& other) {
        //_size = other._size;
        if (!other._str) {
            init();
        }else {
            _capaciity = other._size + 1;
            _str = (char*)nc_malloc(_capaciity);
            _size = other._size;
            memcpy(_str, other._str, _size);
            _str[_size] = 0;
        }
    }

    CStr(CStr& other) {
        //_size = other._size;
        if (!other._str) {
            init();
        }else {
            _capaciity = other._size + 1;
            _str = (char*)nc_malloc(_capaciity);
            _size = other._size;
            memcpy(_str, other._str, _size);
            _str[_size] = 0;
        }
    }

    

    CStr(CStr&& other) {
        swap(other);
    }

    CStr(const CStr&& other) {
        if (!other._str) {
            init();
        }else {
            _capaciity = other._size + 1;
            _str = (char*)nc_malloc(_capaciity);
            _size = other._size;
            memcpy(_str, other._str, _size);
            _str[_size] = 0;
        }
    }

    CStr(char*& s) {
        printf("CStr(char*& s)\n");
        if (s) {
            _size = strlen(s);
            _capaciity = _size + 1;
            _str = (char*)nc_malloc(_capaciity);
            memcpy(_str, s, _size);
            _str[_size] = 0;
        } else {
            init();
        }
    }

    CStr(const char*& s) {
        printf("CStr(const char*& s)\n");
        if (s) {
            _size = strlen(s);
            _capaciity = _size + 1;
            _str = (char*)nc_malloc(_capaciity);
            memcpy(_str, s, _size);
            _str[_size] = 0;
        } else {
            init();
        }
    }

    CStr(char*&& s) {
        printf("CStr(char*&& s)\n");
        if (s) {
            // _size = strlen(s);
            // _capaciity = _size + 1;
            // _str = (char*)nc_malloc(_capaciity);
            // memcpy(_str, s, _size);
            // _str[_size] = 0;
            _str = s;
            _size = strlen(s);
            _capaciity = _size + 1;
        } else {
           init();
        }
    }

    CStr(const unsigned char*& s) {
        printf("CStr(const unsigned char*& s)\n");
        if (s) {
            _size = strlen((char*)s);
            _capaciity = _size + 1;
            _str = (char*)nc_malloc(_capaciity);
            memcpy(_str, s, _size);
            _str[_size] = 0;
        } else {
            init();
        }
    }

    CStr(unsigned char*&& s) {
        printf("CStr(unsigned char*&& s)\n");
        if (s) {
            // _size = strlen(s);
            // _capaciity = _size + 1;
            // _str = (char*)nc_malloc(_capaciity);
            // memcpy(_str, s, _size);
            // _str[_size] = 0;
            _str = (char*)s;
            _size = strlen((char*)s);
            _capaciity = _size + 1;
        } else {
           init();
        }
    }

    CStr(const char*&& s) {
        printf("CStr(const char*&& s)\n");
        if (s) {
            _size = strlen(s);
            _capaciity = _size + 1;
            _str = (char*)nc_malloc(_capaciity);
            memcpy(_str, s, _size);
            _str[_size] = 0;
        } else {
            init();
        }
    }
    //CStr(const char* data, unsigned int len);
    ~CStr() {
        SAFE_FREE(_str);
    }
public:

    inline  CStr& swap(CStr& other) {
        std::swap(_str, other._str);
        std::swap(_size, other._size);
        std::swap(_capaciity, other._capaciity);
    }
    //CStr& operator=(const CStr& other);
    inline CStr& operator=(const char*& s) {

        unsigned int size_ = strlen(s);
        
        if (_capaciity < size_ + 1) {
            SAFE_FREE(_str);
            _capaciity = size_ + 1;
            _str = (char*)nc_malloc(_capaciity);
            
        }
        memcpy(_str, s, size_);
        _size = size_;
        _str[_size] = 0;

        return *this;
    }

    inline CStr& operator=(char*& s) {
       unsigned int size_ = strlen(s);
        
        if (_capaciity < size_ + 1) {
            SAFE_FREE(_str);
            _capaciity = size_ + 1;
            _str = (char*)nc_malloc(_capaciity);
            
        }
        memcpy(_str, s, size_);
        _size = size_;
        _str[_size] = 0;

        return *this;
    }

    inline CStr& operator=(const char*&& s) {
        unsigned int size_ = strlen(s);
        
        if (_capaciity < size_ + 1) {
            SAFE_FREE(_str);
            _capaciity = size_ + 1;
            _str = (char*)nc_malloc(_capaciity);
            
        }
        memcpy(_str, s, size_);
        _size = size_;
        _str[_size] = 0;

        return *this;
    }

    inline CStr& operator=(char*&& s) {
        unsigned int size_ = strlen(s);
        _str = s;
        _size = size_;
        _capaciity = _size + 1;
        
        // if (_capaciity < size_ + 1) {
        //     SAFE_FREE(_str);
        //     _capaciity = size_ + 1;
        //     _str = (char*)nc_malloc(_capaciity); 
        // }
        // memcpy(_str, s, size_);
        // _size = size_;
        // _str[_size] = 0;

        return *this;
    }

    inline bool operator==(const char*& s) {
        return (strcmp(_str, s) == 0);
    }

    inline bool operator==(const char*&& s) {
        return (strcmp(_str, s) == 0);
    }

    inline bool operator==(char*& s) {
        return (strcmp(_str, s) == 0);
    }

    inline bool operator==(char*&& s) {
        return (strcmp(_str, s) == 0);
    }


    inline CStr& operator=(const CStr& other) {
        if (LIKELY(this != &other)) {
            if (_capaciity < other._size + 1) {
                SAFE_FREE(_str);
                _capaciity = other._size + 1;
                _str = (char*)nc_malloc(_capaciity);
                
            }
            memcpy(_str, other._str, other._size);
            _size = other._size;
            _str[_size] = 0;
        }

        return *this;
    }

    inline CStr& operator=(CStr& other) {
        if (LIKELY(this != &other)) {
            if (_capaciity < other._size + 1) {
                SAFE_FREE(_str);
                _capaciity = other._size + 1;
                _str = (char*)nc_malloc(_capaciity);
                
            }
            memcpy(_str, other._str, other._size);
            _size = other._size;
            _str[_size] = 0;
        }

        return *this;
    }


    inline CStr& operator=(CStr&& other) {
        if (LIKELY(this != &other)) {
            return swap(other);
        }

        return *this;
    }

    inline CStr& operator=(const CStr&& other) {
        if (LIKELY(this != &other)) {
            if (_capaciity < other._size + 1) {
                SAFE_FREE(_str);
                _capaciity = other._size + 1;
                _str = (char*)nc_malloc(_capaciity);
                
            }
            memcpy(_str, other._str, other._size);
            _size = other._size;
            _str[_size] = 0;
        }

        return *this;
    }

    inline CStr& operator+=(char ch) {
        if (_capaciity <= _size + 1) {
            _capaciity += 16;
            _str = (char*)nc_realloc(_str, _capaciity);
        }

        _str[_size] = ch;
        _str[++_size] = 0;
        return *this;
    }

    inline bool operator==(const CStr& other) {
        return (_size == other._size && strcmp(_str, other._str) == 0);
    }

    inline bool operator==(CStr& other) {
        return (_size == other._size && strcmp(_str, other._str) == 0);
    }


    inline bool operator==(const CStr&& other) {
        return (_size == other._size && strcmp(_str, other._str) == 0);
    }

    inline bool operator==(CStr&& other) {
        return (_size == other._size && strcmp(_str, other._str) == 0);
    }

    //CStr& operator+=(const CStr& other);
    //bool parse_net_str(const uint8_t* data, uint32_t len);
public:
    inline const char* str() const {return _str;}
    inline unsigned int size() {return _size;}
    inline unsigned int capaciity() {return _capaciity;}
    inline bool empty() {return (_size == 0);}
    inline void clear() {
        if (_str) {
            _str[0] = 0;
        }
        _size = 0;
    }

    inline CStr& rob(CStr& other) {
        if (this == &other) {
            return *this;
        }
        SAFE_FREE(_str);
        _str = other._str;
        _size = other._size;
        _capaciity = other._capaciity;
        other._str = 0;
        other._size = 0;
        other._capaciity = 0;
        return *this;
    }

    inline CStr& append(char*& data, unsigned int len) {
        unsigned int nl = _size + len + 1;
        if (nl <= _capaciity) {
            assign_without_check(data, len);
            return *this;
        }
        _capaciity += (len + 16);
        _str = (char*)nc_realloc(_str, _capaciity);
        assign_without_check(data, len);
        return *this;
    }

    inline CStr& append(char*&& data, unsigned int len) {
        unsigned int nl = _size + len + 1;
        if (nl <= _capaciity) {
            assign_without_check(data, len);
            return *this;
        }
        _capaciity += (len + 16);
        _str = (char*)nc_realloc(_str, _capaciity);
        assign_without_check(data, len);
        return *this;
    }

private:
    inline void init() {
        _capaciity = 0;
        _size = 0;
        _str = 0;

    }
    inline void assign_without_check(char*& data, unsigned len) {
        memcpy(_str + _size, data, len);
        _size += len;
        _str[_size] = 0;
    }

    inline void assign_without_check(const char*& data, unsigned len) {
        memcpy(_str + _size, data, len);
        _size += len;
        _str[_size] = 0;
    }

private:
    char* _str;
    unsigned int _size;
    unsigned int _capaciity;
};

};

#endif //_STR_H_