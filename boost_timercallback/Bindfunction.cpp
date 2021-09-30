/*****************************************/
/* Copyright: DevelEdu 2013              */
/* Author: sha                           */
/*****************************************/

// bindanyfunction.cpp : Defines the entry point for the console application.
//

#include <string>
#include <iostream>
#include <mutex>
#include <functional>
#include "Events.hpp"
#include "Timer.hpp"

std::mutex stdioProt;


void freeFunction(const std::shared_ptr<Event> &event) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);

    if (typeid(*event).name() == typeid(Event).name()) {
        std::cout << "Event triggered: " << event << std::endl;
        return;
    }

    std::cout << "EventOther triggered: " << event << std::endl;
}


void withAnExtra(const std::shared_ptr<Event> &event, const std::string text) {
    // Protecting stdio since its not thread safe
    std::lock_guard<std::mutex> lock(stdioProt);

    std::cout << "Event triggered: " << event << " - With text: " << text << std::endl;
}


class ReferenceObj {
public:
    ReferenceObj() : called_(0) {
    }

    void call(const std::shared_ptr<Event> &event) {
        // Protecting stdio since its not thread safe
        std::lock_guard<std::mutex> lock(stdioProt);

        /* MISSING EVENT PRINT OUT */

        ++called_;
    }

    int gotCalled() {
        return called_;
    }

private:
    int called_;
};

class functor {
public:
    functor() = default;

    void operator()(const std::shared_ptr<Event> &event) {
        std::cout << "Callback in functor called: " << event << std::endl;
    }
};

int main() {
    // Try to make several timers with different callbacks

    ReferenceObj referenceObj;

    Timer t1(4);
    t1.attach(freeFunction);
    t1.attach(functor());
    t1.attach(std::bind(withAnExtra,std::placeholders::_1, "Hej"));
    t1.attach(std::bind(&ReferenceObj::call, &referenceObj, std::placeholders::_1));

    // The threads run naturally in the background (no clean up has been added for the threads)


    // You might wanna change the loop below such that you can extract the value of called_
    //  from your instance of ReferenceObj

    for (;;) {
        std::chrono::milliseconds sleepFor(1000);
        std::this_thread::sleep_for(sleepFor);
        {
            std::lock_guard<std::mutex> lock(stdioProt);
            std::cout << "Got called: " << referenceObj.gotCalled() << std::endl;
        }
    }


    return EXIT_SUCCESS;
}
