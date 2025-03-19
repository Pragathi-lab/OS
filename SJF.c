#include <stdio.h>
#include <stdbool.h>
struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};
void sjf_non_preemptive(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    bool is_completed[n];
    for (int i = 0; i < n; i++) is_completed[i] = false;

    while (completed != n) {
        int shortest = -1;
        int min_burst = 9999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && !is_completed[i] && processes[i].burst < min_burst) {
                min_burst = processes[i].burst;
                shortest = i;
            }
        }
        if (shortest == -1) {
            current_time++;
            continue;
        }
        current_time += processes[shortest].burst;
        processes[shortest].completion = current_time;
        processes[shortest].turnaround = processes[shortest].completion - processes[shortest].arrival;
        processes[shortest].waiting = processes[shortest].turnaround - processes[shortest].burst;
        is_completed[shortest] = true;
        completed++;
    }
}
void sjf_preemptive(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    bool is_completed[n];
    for (int i = 0; i < n; i++) {
        is_completed[i] = false;
        processes[i].remaining = processes[i].burst;
    }
    while (completed != n) {
        int shortest = -1;
        int min_remaining = 9999;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && !is_completed[i] && processes[i].remaining < min_remaining) {
                min_remaining = processes[i].remaining;
                shortest = i;
            }
        }
        if (shortest == -1) {
            current_time++;
            continue;
        }
        processes[shortest].remaining--;
        current_time++;
        if (processes[shortest].remaining == 0) {
            processes[shortest].completion = current_time;
            processes[shortest].turnaround = processes[shortest].completion - processes[shortest].arrival;
            processes[shortest].waiting = processes[shortest].turnaround - processes[shortest].burst;
            is_completed[shortest] = true;
            completed++;
        }
    }
}
void display_results(struct Process processes[], int n) {
    printf("Process\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n",
               processes[i].id, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].waiting, processes[i].turnaround);
    }
}
int main() {
    int n, choice;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
    }
    printf("\nSelect scheduling algorithm:\n");
    printf("1. SJF Non-Preemptive\n");
    printf("2. SJF Preemptive\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        sjf_non_preemptive(processes, n);
    } else if (choice == 2) {
        sjf_preemptive(processes, n);
    } else {
        printf("Invalid choice!\n");
        return 1;
    }
    printf("\nScheduling Results:\n");
    display_results(processes, n);
    return 0;
}
