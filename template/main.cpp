#include <iostream>
#include <vector>
#include "MyArray.h"


int main() {

    MyArray<int, 3> myArray;

    std::vector<int> myVector;
    myVector.push_back(15);
    myVector.push_back(15);

    myArray.fill(15);



    int sum = myAccumulation(myArray);

    std::cout << sum << std::endl;

    return 0;
}