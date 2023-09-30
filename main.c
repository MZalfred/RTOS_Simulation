#include <pthread.h>
#include <unistd.h> // for sleep function
#include <stdio.h>
#include <time.h>
#include "scheduler.h"

FILE *logFile = NULL;

void logToFile(char *message) {
    if(logFile == NULL) {
        logFile = fopen("tasklog.txt", "w");
    }
    fprintf(logFile, "%s\n", message);
    fflush(logFile);
}

void task1() {
    logToFile("Task 1 running");
    printf("Task 1  running\n");
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

Task tasks[] = {
    {task1, 1, 3, 0}, // Run every 3 second
    {task2, 2, 5, 0}, // Run every 5 seconds
    {task3, 3, 7, 0}, // Run every 7 seconds
    {task4, 4, 10, 0}, // Run every 10 seconds
};


// Thread function wrapper
void *threadFunc(void *arg) {
    Task *task = (Task *)arg;
    task->taskFunc();
    return NULL;
}

// Function to sort tasks based on priority
void sortTasks() {
    int n = sizeof(tasks) / sizeof(Task);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (tasks[j].priority > tasks[j+1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j+1];
                tasks[j+1] = temp;
            }
        }
    }
}

// Scheduler function with system clock
void scheduler() {
    int systemTime = 0;  // Initialize system clock
    while (1) {
        for (int i = 0; i < sizeof(tasks)/sizeof(Task); i++) {
            if ((systemTime - tasks[i].lastRun) >= tasks[i].interval) {
                printf("Starting task with priority: %d\n", tasks[i].priority);
                tasks[i].taskFunc();
                printf("Completed task with priority: %d\n", tasks[i].priority);
                tasks[i].lastRun = systemTime;
            }
        }
        sleep(1);  // Simulate a "system clock tick" every 1 second
        systemTime++;
    }
}

// Add logic here
void getUserInput() {
    int choice;
    printf("Press 1 to add task, 2 to change priority\n");
    scanf("%d", &choice);
    // For now, let's just print the choice
    printf("You selected %d", choice);
}

// Main function
int main() {
    printf("RTOS Simulation starting...\n");
    logToFile("RTOS Simulation starting...\n");

    clock_t start, end;
    double cpu_time_used;

    // start the clock
    start = clock();

    // call your schedule or other functions here
    sortTasks();
    scheduler();

    // stop the clock
    end = clock();

    // calculate CPU time used
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("CPU time used: %f\n", cpu_time_used);

    return 0;
}
