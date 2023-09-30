#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct {
    void (*taskFunc)();
    int priority;
    int interval;
    int lastRun;
} Task;

void tasks1();
void tasks2();
void sortTasks();
void scheduler();

#endif // SCHEDULER_H
