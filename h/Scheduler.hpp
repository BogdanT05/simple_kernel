#ifndef PROJECT_SCHEDULER_HPP
#define PROJECT_SCHEDULER_HPP

class Thread;

class Scheduler {
public:
    static Thread* get();
    static void put(Thread* thread);

private:
    static Thread* head;
    static Thread* tail;
};


#endif //PROJECT_SCHEDULER_HPP
