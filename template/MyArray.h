//
// Created by claus on 09/09/2021.
//

#ifndef TEMPLATE_MYARRAY_H
#define TEMPLATE_MYARRAY_H

template<class T, size_t s>
class MyArray {
public:
    MyArray();

    ~MyArray();

    template<class U, size_t s2>
    MyArray(MyArray<U, s2> &);

    void fill(const T &);

    T * begin() const;

    T *end() const;

    T &operator[](int i);

    template<class U, size_t s2>
    MyArray &operator=(MyArray<U, s2> &myArray);

    size_t size() const;

    typedef T value_type;

private:
    T array_[s];
};

#include "MyArray_ptr.h"

template<class T, size_t s>
MyArray<T, s>::MyArray() {

}

template<class T, size_t s>
MyArray<T, s>::~MyArray() {

}

template<class T, size_t s>
void MyArray<T, s>::fill(const T &o) {
    for (size_t i = 0; i < s; i++) {
        array_[i] = o;
    }
}

template<class T, size_t s>
T * MyArray<T, s>::begin() const{
    return array_;
}

template<class T, size_t s>
T *MyArray<T, s>::end() const{
    return array_ + s;
}

template<class T, size_t s>
T &MyArray<T, s>::operator[](int i) {
    return array_[i];
}

template<class T, size_t s>
size_t MyArray<T, s>::size() const {
    return s;
}

template<class T, size_t s>
template<class U, size_t s2>
MyArray<T, s>::MyArray(MyArray<U, s2> &cp): MyArray<T, s>() {
    for (int i = 0; i < s && i < s2; i++) {
        array_[i] = cp[i];
    }
}

template<class T, size_t s>
template<class U, size_t s2>
MyArray<T, s> &MyArray<T, s>::operator=(MyArray<U, s2> &cp) {
    for (int i = 0; i < s && i < s2; i++) {
        array_[i] = cp[i];
    }

    return *this;
}

template<typename T, typename U>
T *myfind(T *first, T *last, const U &v) {
    T *index = first;

    while (index != last) {
        if ((*index) == v) {
            break;
        }
        index++;
    }
    return index;
}

#endif //TEMPLATE_MYARRAY_H