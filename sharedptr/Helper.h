//
// Created by claus on 02/09/2021.
//

#ifndef SHAREDPTR_HELPER_H
#define SHAREDPTR_HELPER_H

template<typename T>
class HelperInterface {
public:
    virtual void execute(T *object) = 0;
    virtual ~HelperInterface() = default;
};
template<typename T, typename D>
class Helper : public HelperInterface<T> {
public:
    Helper(D d) : d_(new D(d)) {}
    void execute(T *object) { // Call d as functor with object as parameter
        (d_->D::operator())(object);
    }
    ~Helper() {
        delete d_;
    }
private:
    D* d_;
};

#endif //SHAREDPTR_HELPER_H
