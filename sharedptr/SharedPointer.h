//
// Created by claus on 02/09/2021.
//

#ifndef SHAREDPTR_SHAREDPOINTER_H
#define SHAREDPTR_SHAREDPOINTER_H

#include "Helper.h"

namespace myspace {
    template<typename T>
    class SharedPointer {
    public:
        explicit SharedPointer(T *t);

        /*
         * void f(SharedPointer s){}
         * Y y;
         * f(&y);
         * == fyfy
         */

        SharedPointer(const SharedPointer &);

        template<typename T, typename D>
        explicit SharedPointer(T *t, D d) : SharedPointer(t) {
            h_ = new Helper<T, D>(d);
        } // Ctor for optional functor

        ~SharedPointer();

        SharedPointer &operator=(const SharedPointer &);

        T &operator*();

        T *operator->();

        size_t count();

        explicit operator bool();

        template<typename T, typename U>
        friend bool operator==(SharedPointer<T> &one, SharedPointer<U> &other);

        template<typename T, typename U>
        friend bool operator!=(SharedPointer<T> &one, SharedPointer<U> &other);

    private:
        size_t *count_;
        T *sharedObject_;
        HelperInterface<T> *h_;
    };

}


template<typename T>
myspace::SharedPointer<T>::SharedPointer(T *t) {
    sharedObject_ = t;
    count_ = new size_t(1);
}

template<typename T>
myspace::SharedPointer<T>::SharedPointer(const SharedPointer<T> &other) {
    sharedObject_ = other.sharedObject_;
    count_ = other.count_;
    (*count_)++;
}

template<typename T>
myspace::SharedPointer<T> &myspace::SharedPointer<T>::operator=(const SharedPointer<T> &other) {
    sharedObject_ = other.sharedObject_;
    count_ = other.count_;
    (*count_)++;
}

template<typename T>
myspace::SharedPointer<T>::~SharedPointer() {
    if ((*count_) == 1) {
        if (h_ != nullptr) {
            h_->execute(sharedObject_);

        } else {
            delete sharedObject_;
        }
    }
    (*count_)--;
}

template<typename T>
T& myspace::SharedPointer<T>::operator*() {
    return (*sharedObject_);
}

template<typename T>
T *myspace::SharedPointer<T>::operator->() {
    return (*sharedObject_);
}

template<typename T>
size_t myspace::SharedPointer<T>::count() {
    return *count_;
}

template<typename T>
myspace::SharedPointer<T>::operator bool() {
    if (*count_ < 1 || sharedObject_ == nullptr) {
        return false;
    }
    return true;
}

template<typename T, typename U>
bool operator!=(myspace::SharedPointer<T> &one, myspace::SharedPointer<U> &other) {
    return one.sharedObject_ != other.sharedObject_;
}

template<typename T, typename U>
bool operator==(myspace::SharedPointer<T> &one, myspace::SharedPointer<U> &other) {
    return one.sharedObject_ == other.sharedObject_;
}


#endif //SHAREDPTR_SHAREDPOINTER_H
