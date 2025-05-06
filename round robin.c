#include <stdio.h>

struct process_rr {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turn_around_time;
    int waiting_time;
    int response_time;
};

void calculate_times(struct process_rr p[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                if (current_time < p[i].arrival_time) {
                    current_time = p[i].arrival_time;  // Jump to arrival time if idle
                }

                if (p[i].remaining_time > quantum) {
                    current_time += quantum;
                    p[i].remaining_time -= quantum;
                } else {
                    current_time += p[i].remaining_time;
                    p[i].completion_time = current_time;
                    p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
                    p[i].response_time = p[i].waiting_time;  // Same as waiting time in RR
                    p[i].remaining_time = 0;
                    completed++;
                }
            }
        }
    }
}

void display_process_details(struct process_rr p[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].process_id, p[i].arrival_time, p[i].burst_time, p[i].completion_time, p[i].turn_around_time, p[i].waiting_time, p[i].response_time);
    }
}

void calculate_averages(struct process_rr p[], int n) {
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;

    for (int i = 0; i < n; i++) {
        total_turnaround_time += p[i].turn_around_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
    }

    printf("\nAverages:\n");
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Response Time: %.2f\n", (float)total_response_time / n);
}

int main() {
    int n, quantum;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process_rr processes[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Process %d:\n", i + 1);
        processes[i].process_id = i + 1;  // Assign Process ID starting from 1
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;  // Initialize remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    // Sort processes by arrival time (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct process_rr temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Calculate times and averages
    calculate_times(processes, n, quantum);
    display_process_details(processes, n);
    calculate_averages(processes, n);

    return 0;
}
