#ifndef PROJECT_THREAD_HPP
#define PROJECT_THREAD_HPP
#include "../lib//hw.h"

enum State {
    CREATED = 0,
    READY = 1,
    RUNNING = 2,
    FINISHED = 3
};

class Thread {
private:
    void (*body)(void*);
    void *arg;
    State state;

public:
    Thread(void (*body)(void*), void* arg);

    Thread *next;
    static Thread* running;

    static void dispatch();
    int start();
};


#endif //PROJECT_THREAD_HPP
