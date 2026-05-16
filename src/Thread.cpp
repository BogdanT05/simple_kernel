#include "../h/Thread.hpp"

Thread* Thread::running = nullptr;

Thread::Thread(void(*body)(void *), void *arg) : body(body), arg(arg), state(CREATED) {
    next = nullptr;
}

void Thread::dispatch() {
    if (running != nullptr && running->state == RUNNING) {
        running->state = READY;
        // scheduler vraca nit
    }

    running = ... // scheduler postalvja novu nit

    if (running != nullptr)
        running->state = RUNNING;
}

int Thread::start() {
    if (state == CREATED) {
        state = READY;
        // Ubacivanje u Scheduler
        return 0;
    }

    return -1;
}
