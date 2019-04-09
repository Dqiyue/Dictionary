/**
 * 
 * @author:          kylin
 * @email:           kylin.du@outlook.com
 * @dateTime:        2019-04-09 Tue 09:48:18
 * @description:     hash val
 * @Copyright:       kylin.du
 * 
 */

#ifndef _HASH_H_
#define _HASH_H_


#include "str.h"

namespace NetCore {

class CHash {
public:
    static inline unsigned int gethash(unsigned int val) {
        return val;
    }

    static inline unsigned int gethash(int val) {
        return (unsigned int)val;
    }

    static inline unsigned int gethash(char*& str) {
        unsigned int seed = 131;
        unsigned int hash = 0;
        while (*str) {
            hash = hash * seed + *(str++);
        }
        return (hash & 0x7fffffff);
    }

    static inline unsigned int gethash(char*&& str) {
        unsigned int seed = 131;
        unsigned int hash = 0;
        while (*str) {
            hash = hash * seed + *(str++);
        }
        return (hash & 0x7fffffff);
    }

    static inline unsigned int gethash(const char*& str) {
        unsigned int seed = 131;
        unsigned int hash = 0;
        while (*str) {
            hash = hash * seed + *(str++);
        }
        return (hash & 0x7fffffff);
    }

    static inline unsigned int gethash(const char*&& str) {
        unsigned int seed = 131;
        unsigned int hash = 0;
        while (*str) {
            hash = hash * seed + *(str++);
        }
        return (hash & 0x7fffffff);
    }

    static inline unsigned int gethash(CStr&& str) {
        return gethash(str.str());
    }

    static inline unsigned int gethash(CStr& str) {
        return gethash(str.str());
    }
};

};

#endif //_HASH_H_