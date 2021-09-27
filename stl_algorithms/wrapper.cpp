//
// Created by claus on 27/09/2021.
//

#include <iostream>
#include <functional>

template <class T>
class Wrapper {
public:
    explicit Wrapper(std::function<void(T)> f) :f_(f), t_ref(*(new T)) {}
    Wrapper(const Wrapper& w): f_(w.f_), t_ref(w.t_ref) {}

    Wrapper& operator=(const Wrapper& w) {
        t_ref = w.t_ref;
        f_ = w.f_;
        return *this;
    }

    Wrapper& operator++() {
        f_(t_ref);
        return *this;
    }

    T& operator*() {
        return t_ref;
    }

private:
    std::function<void(T)> f_;
    T & t_ref;
};


class Test {
public:
    void printExt(int i) const {
        std::cout << "i: " << i << std::endl;
    }
};

