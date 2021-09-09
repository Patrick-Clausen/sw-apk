//
// Created by claus on 02/09/2021.
//

#ifndef SHAREDPTR_GENERICDELETER_H
#define SHAREDPTR_GENERICDELETER_H

#include <iostream>
#include "SharedPointer.h"

template<typename T>
class GenericDeleter {
public:
    int operator()(T *);
};

template<typename T>
int GenericDeleter<T>::operator()(T *object) {
    std::cout << "Deleting object from functor!!" << std::endl;
    delete object;
    return 0;
}


#endif //SHAREDPTR_GENERICDELETER_H
