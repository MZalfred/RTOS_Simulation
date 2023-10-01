#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef struct {
    void (*taskFunc)();
    int priority;
    int interval;
    int lastRun;
} Task;

void task1();  // Corrected from tasks1
void task2();  // Corrected from tasks2
void sortTasks();
void scheduler(int systemTime);  // Only one scheduler declaration with systemTime parameter

#endif // SCHEDULER_H