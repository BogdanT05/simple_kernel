#include "../h/Scheduler.hpp"
#include "../h/Thread.hpp"

Thread* Scheduler::head = nullptr;
Thread* Scheduler::tail = nullptr;

Thread * Scheduler::get() {
    if (head == nullptr)
        return nullptr;

    Thread* nextThread = head;
    head = head->next;

    if (head == nullptr)
        tail = nullptr;

    nextThread->next = nullptr;
    return nextThread;
}

void Scheduler::put(Thread *thread) {
    if (thread == nullptr)
        return;

    thread->next = nullptr;

    if (head == nullptr) {
        head = thread;
        tail = thread;
        return;
    }

    tail->next = thread;
    tail = thread;
}
