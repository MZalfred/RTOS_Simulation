#include <stdio.h>

// simuating a task structure
struct Task {
    char *name;
    int priority;
};

// simulating a task structure
void schedule(struct Task tasks[], int n) {
    printf("Scheduling tesk...\n");
    for (int i = 0; i < n; i++) {
        printf("Runing %s with priority %d\n", tasks[i].name, tasks[i].priority);
    }
}

int main() {
    struct Task tasks[] = {
        {"Task1", 1},
        {"Task2", 2},
        {"Task3", 3},
    };

    int n = sizeof(tasks)/sizeof(tasks[0]);
    schedule(tasks, n);

    return 0;
}
