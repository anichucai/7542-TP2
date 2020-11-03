#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
 public:
    Thread() {}
    void start() {
        thread = std::thread(&Thread::run, this);
    }
    void join() {
        thread.join();
    }
    virtual void run() = 0;
    virtual ~Thread() {}
 private:
    std::thread thread;
};

#endif    // THREAD_H
