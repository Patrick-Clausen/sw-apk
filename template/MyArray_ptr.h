//
// Created by claus on 16/09/2021.
//

#ifndef TEMPLATE_MYARRAY_PTR_H
#define TEMPLATE_MYARRAY_PTR_H

#include "MyArray.h"


template<class T, size_t s>
class MyArray<T *, s> {
public:
    MyArray();

    ~MyArray();

    template<class U, size_t s2>
    MyArray(MyArray<U *, s2> &);

    void fill(const T *&);

    T * begin() const;

    T **end();

    T *&operator[](int i);

    template<class U, size_t s2>
    MyArray &operator=(MyArray<U *, s2> &myArray);

private:
    T *array_[s];

    void clearArray();
    void clearIndex(size_t);
};

template<class T, size_t s>
MyArray<T *, s>::MyArray() {
    for (size_t i = 0; i < s; i++) {
        array_[i] = nullptr;
    }
}

template<class T, size_t s>
void MyArray<T *, s>::clearArray() {
    for (size_t i = 0; i < s; i++) {
        clearIndex(i);
    }
}

template<class T, size_t s>
void MyArray<T*, s>::clearIndex(size_t i) {
    if(array_[i] != nullptr) {
        delete array_[i];
        array_[i] = nullptr;
    }
}

template<class T, size_t s>
MyArray<T *, s>::~MyArray() {
    clearArray();
}

template<class T, size_t s>
void MyArray<T *, s>::fill(const T *&o) {
    clearArray();
    for (size_t i = 0; i < s; i++) array_[i] = new T(*o);
}

template<class T, size_t s>
T * MyArray<T *, s>::begin() const {
    return array_;
}

template<class T, size_t s>
T **MyArray<T *, s>::end() {
    return array_ + s;
}

template<class T, size_t s>
T *&MyArray<T *, s>::operator[](int i) {
    return array_[i];
}

template<class T, size_t s>
template<class U, size_t s2>
MyArray<T *, s>::MyArray(MyArray<U *, s2> &cp): MyArray<T *, s>() {
    for (int i = 0; i < s && i < s2; i++) {
        if(cp[i] != nullptr) {
            array_[i] = new T(*cp[i]);
        }
    }
}

template<class T, size_t s>
template<class U, size_t s2>
MyArray<T *, s> &MyArray<T *, s>::operator=(MyArray<U *, s2> &cp) {
    for (int i = 0; i < s && i < s2; i++) {
        clearIndex(i);
        array_[i] = cp[i];
    }

    return *this;
}


template<typename T, typename U>
T **myfind(T **first, T **last, const U &v) {
    T **index = first;

    while (index != last) {
        if ((**index) == v) {
            break;
        }
        index++;
    }
    return index;
}


#endif //TEMPLATE_MYARRAY_PTR_H
