#include <iostream>
#include <boost/signals2.hpp>

void freeFunction(const std::string &sensorName, double sensorValue) {
    std::cout << "|FREE FUNCTION| Sensor name: " << sensorName << std::endl << "Sensor value: " << sensorValue
              << std::endl;
}

class Functor {
public:
    void operator()(const std::string &sensorName, double sensorValue) {
        std::cout << "|FUNCTOR| Sensor name: " << sensorName << std::endl << "Sensor value: " << sensorValue
                  << std::endl;
    }
};

class MyClass {
public:
    void memberFunction(const std::string &sensorName, double sensorValue) {
        std::cout << "|MEMBER FUNCTION| Sensor name: " << sensorName << std::endl << "Sensor value: " << sensorValue
                  << std::endl;
    }
};

int main() {
    auto lambda = [](const std::string &sensorName, double sensorValue) -> void {
        std::cout << "|LAMBDA| Sensor name: " << sensorName << std::endl << "Sensor value: " << sensorValue
                  << std::endl;
    };

    MyClass instance;

    boost::signals2::signal<void(const std::string &, double sensorValue)> sig;

    sig.connect(&freeFunction);
    sig.connect(Functor());
    sig.connect(std::bind(&MyClass::memberFunction, &instance, std::placeholders::_1, std::placeholders::_2));
    sig.connect(lambda);

    sig("some sensor", 15.4);

    return 0;
}