//
// Created by claus on 01/10/2021.
//

#include <iostream>
#include <boost/signals2.hpp>

double f1(double one, double two, double three) {
    return one;
}

double f2(double one, double two, double three) {
    return one;
}

double f3(double one, double two, double three) {
    return two;
}

double f4(double one, double two, double three) {
    return three;
}

template <typename T>
struct median{
    typedef T result_type;

    template<typename InputIterator>
    T operator() (InputIterator first, InputIterator last) const {
        T med = T();
        size_t count = 0;
        for(; first != last; first++) {
            med += *first;
            count++;
        }

        return med/count;
    }
};

int main() {
    boost::signals2::signal<double(double, double, double), median<double>> sig;

    sig.connect(&f1);
    sig.connect(&f2);
    sig.connect(&f3);
    sig.connect(&f4);

    double result = sig(10, 20, 60);

    assert(result == 25);

    return 0;
}