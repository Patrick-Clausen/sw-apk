#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <string>
#include <map>
#include <thread>
#include <functional>
#include <chrono>

class Timer {
public:
    explicit Timer(int timer = 10);

    ~Timer();

    int attach(std::function<void(const std::shared_ptr<Event> &)> cb);

    void detach(int cbId);

    void notifyAll(const std::shared_ptr<Event> &any);

private:
    int timerThreadFunction();

private:
    typedef std::function<void(const std::shared_ptr<Event> &)> callback;
    std::map<int, callback> callbacks_;
    int callbackIndex_ = 0;
    int eventTimer_;
    std::thread *thread_;
    bool terminator_;
};

#endif