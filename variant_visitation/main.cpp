#include <iostream>
#include <boost/variant.hpp>
#include <variant>

class UserDefined {
public:
    int x = 0;
};

std::ostream& operator<<(std::ostream& str, const UserDefined& ref) {
    return str << "UserDefined.x = " << ref.x << std::endl;
}

class VisitationClass : public boost::static_visitor<void> {
public:
    void operator()(const UserDefined& u) {
        std::cout << u << std::endl;
    }

    void operator()(int i) {
        std::cout << i << std::endl;
    }

    void operator()(const std::string& s) {
        std::cout << s << std::endl;
    }
};


int main() {
    std::variant<UserDefined, int, std::string> myVariant;

    std::visit(VisitationClass(), myVariant);
    return 0;
}
