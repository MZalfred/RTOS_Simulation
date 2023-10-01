#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "scheduler.h"

void removeTask(int taskIndex); // Declare this at the top

Task *tasks = NULL;
int taskCount = 0;
FILE *logFile = NULL;

void logToFile(char *message) {
    if(logFile == NULL) {
        logFile = fopen("tasklog.txt", "w");
    }
    fprintf(logFile, "%s\n", message);
    fflush(logFile);
}

void addTask(void (*newTaskFunc)(), int priority, int interval) {
    taskCount++;
    tasks = realloc(tasks, taskCount * sizeof(Task));
    if(tasks == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
    tasks[taskCount - 1].taskFunc = newTaskFunc;
    tasks[taskCount - 1].priority = priority;
    tasks[taskCount - 1].interval = interval;
    tasks[taskCount - 1].lastRun = 0;
}

void task1() {
    logToFile("Task 1 running");
    printf("Task 1 running\n");
}

void task2() {
    logToFile("Task 2 running");
    printf("Task 2 running\n");
}

void task3() {
    logToFile("Task 3 running");
    printf("Task 3 running\n");
}

void task4() {
    logToFile("Task 4 running");
    printf("Task 4 running\n");
}

void sortTasks() {
    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void scheduler(int systemTime) {
    for (int i = 0; i < taskCount; i++) {
        if ((systemTime - tasks[i].lastRun) >= tasks[i].interval) {
            printf("Starting task with priority: %d\n", tasks[i].priority);
            tasks[i].taskFunc();
            printf("Completed task with priority: %d\n", tasks[i].priority);
            tasks[i].lastRun = systemTime;
        }
    }
    sleep(1);
}

void removeTask(int taskIndex) {
    for(int i = taskIndex; i < taskCount - 1; i++) {
        tasks[i] = tasks[i+1];
    }
    taskCount--;
    tasks = realloc(tasks, taskCount * sizeof(Task));
    if(tasks == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(1);
    }
}

int main() {
    addTask(task1, 1, 3);
    addTask(task2, 2, 5);
    addTask(task3, 3, 7);
    addTask(task4, 4, 10);
    
    printf("RTOS Simulation starting...\n");
    logToFile("RTOS Simulation starting...");
    
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    sortTasks();
    
    int systemTime = 0;
    int maxTime = 60;
    
    while (systemTime < maxTime) {
        scheduler(systemTime);
        systemTime++;
    }
    
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f\n", cpu_time_used);
    
    fclose(logFile);  // Close log file
    free(tasks);  // Free dynamically allocated memory
    
    return 0;
}
