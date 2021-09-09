#include <iostream>
#include "SharedPointer.h"
#include "GenericDeleter.h"

class A{};

class B : public A {};

using namespace myspace;

int main() {

    SharedPointer ptr = SharedPointer<B>(new B(), GenericDeleter<B>());


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
