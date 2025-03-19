#include <stdio.h>

struct Process {
    int pid;
    int at;  // Arrival Time
    int bt;  // Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
};

// Function to sort processes by Arrival Time
void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to calculate Completion Time, Turnaround Time, and Waiting Time
void calculateTimes(struct Process p[], int n) {
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        if (currentTime < p[i].at) {
            currentTime = p[i].at;
        }
        p[i].ct = currentTime + p[i].bt;  // Completion Time = Current Time + Burst Time
        p[i].tat = p[i].ct - p[i].at;    // Turnaround Time = Completion Time - Arrival Time
        p[i].wt = p[i].tat - p[i].bt;     // Waiting Time = Turnaround Time - Burst Time
        currentTime = p[i].ct;            // Update current time to process completion time
    }
}

// Function to display process details
void displayProcess(struct Process p[], int n) {
    printf("\n PID\t AT \tBT \tCT\t TAT \tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

// Function to calculate average Turnaround Time and Waiting Time
void calculateAverageTimes(struct Process p[], int n) {
    int totalTAT = 0, totalWT = 0;
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
    }
    float avgTAT = (float)totalTAT / n;
    float avgWT = (float)totalWT / n;
    printf("\nAverage Turnaround Time: %.2f", avgTAT);
    printf("\nAverage Waiting Time: %.2f\n", avgWT);
}

int main() {
    int n = 0, choice;
    struct Process p[50];
    do {
        printf("\n CPU Scheduling FCFS\n");
        printf("1. Enter process details\n");
        printf("2. Compute scheduling time\n");
        printf("3. Display Results\n");
        printf("4. Calculate Average TAT and WT\n");
        printf("5. Exit \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of processes: ");
                scanf("%d", &n);
                printf("Enter Arrival Time and Burst Time for each process:\n");
                for (int i = 0; i < n; i++) {
                    p[i].pid = i + 1;
                    printf("Process %d - AT BT: ", i + 1);
                    scanf("%d %d", &p[i].at, &p[i].bt);
                }
                printf("Process details recorded\n");
                break;

            case 2:
                if (n == 0) {
                    printf("No process available! Please enter process details first.\n");
                } else {
                    sortByArrival(p, n);
                    calculateTimes(p, n);
                    printf("Scheduling computed successfully.\n");
                }
                break;

            case 3:
                if (n == 0) {
                    printf("No process details! Please enter process details.\n");
                } else {
                    displayProcess(p, n);
                }
                break;

            case 4:
                if (n == 0) {
                    printf("No process details available! Please enter process details.\n");
                } else {
                    calculateAverageTimes(p, n);
                }
                break;

            case 5:
                printf("Exiting program\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
