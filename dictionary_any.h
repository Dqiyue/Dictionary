/**
 * 
 * @author:          kylin
 * @email:           kylin.du@outlook.com
 * @dateTime:        2019-04-09 Tue 09:48:18
 * @description:     a simple dictionary
 * @Copyright:       kylin.du
 * 
 */

#ifndef _DICTIONARY_ANY_H_
#define _DICTIONARY_ANY_H_


#include "hash.h"
#include "any.h"
#include "str.h"
#include <assert.h>

namespace NetCore {

// inline unsigned int roundup_pow_of_two(unsigned int size) {
// 	if (size == 0) {
// 		return 0;
// 	}
// 	if (size >= 0x80000000) {
// 		return 0x80000000;
// 	}

// 	unsigned int i = 0;
// 	--size;
// 	while ((size >> (++i)) != 0);
// 	return (((unsigned int)1) << i);
// }

class dictionary_any {
public:
    enum {DEFAULT_BUCKETS_NUM = 8, MIN_BUCKETS = 2, BASE_ELEM_NUM = 4};
    inline static unsigned int roundup_pow_of_two(unsigned int size) {
        if (size == 0) {
            return 0;
        }
        if (size >= 0x80000000) {
            return 0x80000000;
        }

        unsigned int i = 0;
        --size;
        while ((size >> (++i)) != 0);
        return (((unsigned int)1) << i);
    }
    typedef struct  elem{
        elem() {next = 0;}
        ~elem() = default;
        elem& operator=(const elem& e) {
            key = e.key;
            val = e.val;
            next = e.next;
            hash = e.hash;
            return *this;
        }

        elem& operator=(elem&& e) {
            key = std::move(e.key);
            val = std::move(e.val);
            next = e.next;
            hash = e.hash;
            return *this;
        }

        friend class dictionary_any;
        unsigned int hash;
        any val;
        any key;
        //template <typename T>
        //const typename std::remove_cv<T>::type& getkey() const {return *(key.get<T>());}
    private:
        //any key;
        unsigned int next; //the key to next elem
    }* iterator;
public:
    dictionary_any(unsigned int buckets_num = DEFAULT_BUCKETS_NUM) {
        _bucket_num = (buckets_num <= MIN_BUCKETS ? MIN_BUCKETS : roundup_pow_of_two(buckets_num));
        _buckets = (unsigned int*)nc_malloc(sizeof(unsigned int) * _bucket_num);
        memset(_buckets, 0, sizeof(unsigned int) * _bucket_num);
        _size = 0;
        //_dsize = 0;
        _esize = MAX(_bucket_num, BASE_ELEM_NUM);
        _entry = new elem[_esize + 1];
        //_entry = (iterator)nc_malloc(sizeof(struct elem) * _esize);
        // for(unsigned i = 0; i < _esize; ++i) {
        //     (_entry[i]).next = 0;
        // }
        //memset(_entry, 0, sizeof(struct elem) * _esize);
        //_dentry = _entry;
    }

    dictionary_any(const dictionary_any& dict) {
        _bucket_num = dict._bucket_num;
        _buckets = (unsigned int*)nc_malloc(sizeof(unsigned int) * _bucket_num);
        memcpy((char*)_buckets, (char*)dict._buckets, sizeof(unsigned int) * _bucket_num);
        _size = dict._size;
        _esize = dict._esize;
        _entry = new elem[_esize + 1];
        for (unsigned int i = 0; i < _esize + 1; ++i) {
            _entry[i] = dict._entry[i];
        }
    }


    dictionary_any(dictionary_any&& dict) {
        //release();
        this->swap(dict);
    }

    virtual ~dictionary_any() {
        SAFE_FREE(_buckets);
        if (_entry) {
            delete[] _entry;
        }
    }
public:
    void clear() {
        memset(_buckets, 0, sizeof(unsigned int) * _bucket_num);
        _size = 0;
    }

    void swap(dictionary_any& dict) {
        std::swap(_bucket_num, dict._bucket_num);
        std::swap(_buckets, dict._buckets);
        std::swap(_entry, dict._entry);
        std::swap(_size, dict._size);
        std::swap(_esize, dict._esize);
    }
    dictionary_any& operator=(const dictionary_any& dict) {
        SAFE_FREE(_buckets);
        if (_entry) {
            delete[] _entry;
        }
        _bucket_num = dict._bucket_num;
        _buckets = (unsigned int*)nc_malloc(sizeof(unsigned int) * _bucket_num);
        memcpy((char*)_buckets, (char*)dict._buckets, sizeof(unsigned int) * _bucket_num);
        _size = dict._size;
        _esize = dict._esize;
        _entry = new elem[_esize + 1];
        for (unsigned int i = 0; i < _esize + 1; ++i) {
            _entry[i] = dict._entry[i];
        }
    }

    dictionary_any& operator=(dictionary_any&& dict) {
        //this->release();
        this->swap(dict);
    }

    inline unsigned int positionof(unsigned int hash) {
        return _buckets[indexof(hash)];
    }
    inline unsigned int indexof(unsigned int hash) {
        return (hash & (_bucket_num - 1));
    }
    inline iterator begin() {return &(_entry[1]);}
    inline iterator end() {return &(_entry[_size + 1]);}

    inline bool empty() {return (_size == 0);}

    inline bool shrink() {
        if (_size >= (_esize << 1)/5) {
            return true;
        }
        unsigned int ns = MAX(_size >> 1, BASE_ELEM_NUM);

        elem* ne = new elem[ns + 1];
        if (ne == 0) {
            return false;
        }
        for (unsigned int i = 1; i <= _size; ++i) {
            ne[i] = std::move(_entry[i]); 
        }

        elem* temp = _entry;
        _esize = ns;
        _entry = ne;
        //_dentry = _entry;
        delete[] temp;
        return true;
    }

private:
    void release() {
        _bucket_num = 0;
        if(_buckets) {
            free(_buckets);
            _buckets = 0;
        }

        if (_entry) {
            delete[] _entry;
            _entry = 0;
        }
        _size = 0;
        _esize = 0;
    }
    inline iterator noval(){return _entry;}
    
    inline bool full() {return (_size == _esize);}
    
    // inline iterator pop_dentry() {
    //     if (_dsize) {
    //         iterator it = _dentry;
    //         _dentry = &(_entry[it->next]);
    //         --_dsize;
    //         return it;
    //     }
    //     return 0;
    // }

    //make sure the _dsize is 0
    inline bool buckets_negotiation(unsigned int nb) {
        unsigned int n = MAX(nb, MIN_BUCKETS);    
        unsigned int* temp = (unsigned int*)nc_malloc(sizeof(unsigned int) * n);
        if (!temp) {
            return false;
        }
        memset(temp, 0, sizeof(unsigned int) * n);
        unsigned int index = 0;
        for (iterator it = begin(); it != end(); ++it) {
            //index = indexof(CHash::gethash(it->key));
            index = indexof(it->hash);
            it->next = temp[index];
            temp[index] = it - _entry;
        }
        delete[] _buckets;
        _buckets = temp;
        _bucket_num = n;
        printf("-----------buckets_negotiation : new buckets num is %u\n",n);
        return true;
    }

    inline bool auto_negotiation() {
        if (_size <= (_esize << 2)/5 ) {
            return true;
        }

        printf("_size is %u,_bucket_num is %u\n", _size, _bucket_num);
        if (_size > (_bucket_num << 1)) {
            //expand bucket
            printf("-----------start  buckets_negotiation\n");
            (void)buckets_negotiation(_bucket_num << 1);
        }

        //printf("start expand, now addr is 0x%08x\n", (unsigned int)_entry);
        unsigned int ns = _esize << 1;
        elem* ne = new elem[ns + 1];
        if (ne == 0) {
            return false;
        }
        for (unsigned int i = 1; i <= _size; ++i) {
            ne[i] = std::move(_entry[i]); 
        }

        elem* temp = _entry;
        _esize = ns;
        _entry = ne;
        //_dentry = _entry;
        delete[] temp;
        printf("auto_negotiation : new size is %u\n",_esize);
        //printf("end expand, now addr is 0x%08x\n", (unsigned int)_entry);
        return true;
    }

    template <typename T>
    inline iterator find_with_index(T&& key, unsigned int index) {
        unsigned int pos = _buckets[index];
        iterator it = &(_entry[pos]);
        while(it != noval()) {
            if (it->key == std::move(key)) {
                return it;
            }
            it = &(_entry[it->next]);
        }
        return end();
    }

    template <typename T>
    inline iterator find_with_index(const T& key, unsigned int index) {
        unsigned int pos = _buckets[index];
        iterator it = &(_entry[pos]);
        while(it != noval()) {
            if (it->key == key) {
                return it;
            }
            it = &(_entry[it->next]);
        }
        return end();
    }


    template <typename t1, typename t2>
    inline iterator real_insert(t1&& key, t2&& val, unsigned int index, unsigned int hash) {
        //expand
        // use deleted elem from dentry
        // iterator it = pop_dentry();
        // if (0 != it) {
        //     it->key = key;
        //     it->val = val;
        //     it->next = _buckets[index];
        //     _buckets[index] = it - _entry;
        //     return it;
        // } 
        if (auto_negotiation() == false && full()) {
            return end();
        }

        iterator it = end();
        it->key = std::forward<t1>(key);
        it->val = std::forward<t2>(val);
        it->hash = hash;
        it->next = _buckets[index];
        _buckets[index] = ++_size;
        return it;
    }

public: //ops

// find impl
    template <typename T>
    inline iterator find(T&& key) {
        return find_with_index(std::forward<T>(key), indexof(CHash::gethash(key)));
    }

    template <typename T>
    inline iterator find(const T& key) {
        return find_with_index(key, indexof(CHash::gethash(key)));
    }




//insert impl
    template <typename t1, typename t2>
    inline iterator insert(t1&& key, t2&& val) {
        unsigned int hash = CHash::gethash(key);
        unsigned int index = indexof(hash);
        iterator it = find_with_index(key, index);
        if (it != end()) {
            it->val = val;
            return it;
        }

        return real_insert(std::forward<t1>(key), std::forward<t2>(val), index, hash);
    }

    template<typename T>
    inline iterator erase_pre_imp(const T& key, unsigned int index) {
        iterator p = &(_entry[(_buckets[index])]);
        if (p->key == key) {
            _buckets[index] = p->next;
            return p;
        }

        while(p->next != 0) {
            if (_entry[p->next].key == key) {
                iterator it = &_entry[p->next];
                p->next = it->next;
                return it;
            }
            p = &_entry[p->next];
        }
        return end(); 
    }


// erase imp
    // for str
    // inline void erase(CStr&& key) {
    //     unsigned int index = indexof(CHash::gethash(key));
    //     iterator it = erase_pre_imp(key, index);
    //     if (it == end()) {
    //         return;
    //     }

    //     //iterator last = &_entry[_size];
    //     if (it == &_entry[_size]) {
    //         --_size;
    //         return;
    //     }

    //     *it = std::move(_entry[_size]);
    //     index = indexof(CHash::gethash(*(it->key.get<T>())));
    //     assert(_buckets[index] == _size);
    //      _buckets[index] = it - _entry;
    //     --_size;
    //     return;
    // }

    // inline any& operator[](CStr&& key) {
    //     unsigned int hash = CHash::gethash(key);
    //     unsigned int index = indexof(hash);
    //     iterator it = find_with_index(key, index);
    //     if (it == end()) {
    //         it = real_insert(std::forward(key), any(), index, hash);
    //     }
    //     return it->val;
    // }
    //

    template<typename T>
    inline void erase(T&& key) {
        unsigned int index = indexof(CHash::gethash(key));
        iterator it = erase_pre_imp(key, index);
        if (it == end()) {
            return;
        }

        //iterator last = &_entry[_size];
        if (it == &_entry[_size]) {
            --_size;
            return;
        }

        *it = std::move(_entry[_size]);
        index = indexof(it->hash);
        assert(_buckets[index] == _size);
         _buckets[index] = it - _entry;
        --_size;
        return;
    }

    template<typename T>
    inline any& operator[](T&& key) {
        unsigned int hash = CHash::gethash(key);
        unsigned int index = indexof(hash);
        iterator it = find_with_index(std::forward<T>(key), index);
        if (it == end()) {
            it = real_insert(std::forward<T>(key), any(), index, hash);
        }
        return it->val;
    }

    // template<typename T>
    // inline any& operator[](const T& key) {
    //     unsigned int hash = CHash::gethash(key);
    //     unsigned int index = indexof(hash);
    //     iterator it = find_with_index(key, index);
    //     if (it == end()) {
    //         it = real_insert(key, any(), index, hash);
    //     }
    //     return it->val;
    // }



public:
    unsigned int _bucket_num;
    unsigned int* _buckets;
    struct elem* _entry;
    //iterator _dentry; 
    //unsigned int _dsize;
    unsigned int _esize;
    unsigned int _size;
};

};

#endif //_DICTIONARY_ANY_H_