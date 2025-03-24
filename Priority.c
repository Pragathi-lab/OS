#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id;
    int arrival;
    int burst;
    int priority;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
    int start_time;
};

// **Priority Scheduling (Non-Preemptive)**
void priority_non_preemptive(struct Process processes[], int n) {
    int current_time = 0, completed = 0;
    bool is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = false;

    while (completed != n) {
        int highest_priority = -1, min_priority = 9999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && !is_completed[i] && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                highest_priority = i;
            }
        }
        if (highest_priority == -1) {
            current_time++;
            continue;
        }

        current_time += processes[highest_priority].burst;
        processes[highest_priority].completion = current_time;
        processes[highest_priority].turnaround = processes[highest_priority].completion - processes[highest_priority].arrival;
        processes[highest_priority].waiting = processes[highest_priority].turnaround - processes[highest_priority].burst;
        is_completed[highest_priority] = true;
        completed++;
    }
}

// **Priority Scheduling (Preemptive)**
void priority_preemptive(struct Process processes[], int n) {
    int current_time = 0, completed = 0;
    bool is_completed[n];

    for (int i = 0; i < n; i++) {
        is_completed[i] = false;
        processes[i].remaining = processes[i].burst;
        processes[i].start_time = -1; // Indicates that process has not started
    }

    while (completed != n) {
        int highest_priority = -1, min_priority = 9999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && !is_completed[i] && processes[i].remaining > 0 && processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                highest_priority = i;
            }
        }
        if (highest_priority == -1) {
            current_time++;
            continue;
        }

        // If process starts for the first time, set its start_time
        if (processes[highest_priority].start_time == -1) {
            processes[highest_priority].start_time = current_time;
        }

        processes[highest_priority].remaining--;
        current_time++;

        if (processes[highest_priority].remaining == 0) {
            processes[highest_priority].completion = current_time;
            processes[highest_priority].turnaround = processes[highest_priority].completion - processes[highest_priority].arrival;
            processes[highest_priority].waiting = processes[highest_priority].turnaround - processes[highest_priority].burst;
            is_completed[highest_priority] = true;
            completed++;
        }
    }
}

// **Display Results**
void display_results(struct Process processes[], int n) {
    printf("Process\tArrival\tBurst\tPriority\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n",
               processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].priority, processes[i].completion,
               processes[i].waiting, processes[i].turnaround);
    }
}

// **Calculate and Display Averages**
void calculate_averages(struct Process processes[], int n) {
    float total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++) {
        total_waiting += processes[i].waiting;
        total_turnaround += processes[i].turnaround;
    }
    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

// **Main Function**
int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival, &processes[i].burst, &processes[i].priority);
    }

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. Priority Scheduling (Non-Preemptive)\n");
    printf("2. Priority Scheduling (Preemptive)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        priority_non_preemptive(processes, n);
    } else if (choice == 2) {
        priority_preemptive(processes, n);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }

    printf("\nScheduling Results:\n");
    display_results(processes, n);
    calculate_averages(processes, n);

    return 0;
}
