#include <stdio.h>
#include <string.h>

struct Process {
    int pid;
    char name[50];
    int arrivalTime;
    int completionTime;
    int executionTime;
};


void getDetails(struct Process *p) {
    printf("Enter process ID: ");
    scanf("%d", &p->pid);

    printf("Enter process name: ");
    scanf("%s", p->name);

    printf("Enter arrival time: ");
    scanf("%d", &p->arrivalTime);

    printf("Enter completion time: ");
    scanf("%d", &p->completionTime);

    printf("Enter execution time: ");
    scanf("%d", &p->executionTime);
}

void displayDetails(struct Process p) {
    printf("\nProcess ID: %d\n", p.pid);
    printf("Process Name: %s\n", p.name);
    printf("Arrival Time: %d\n", p.arrivalTime);
    printf("Completion Time: %d\n", p.completionTime);
    printf("Execution Time: %d\n", p.executionTime);
}


void searchDetails(struct Process processes[], int n, int pid) {
    int found = 0;
    for (int i = 0; i < n; i++) {
        if (processes[i].pid == pid) {
            found = 1;
            printf("\nProcess found:\n");
            displayDetails(processes[i]);
            break;
        }
    }
    if (!found) {
        printf("\nProcess with PID %d not found.\n", pid);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    int choice, pid;

    do {
        printf("\nMenu:\n");
        printf("1. Enter process details\n");
        printf("2. Display all process details\n");
        printf("3. Search for a process by PID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                for (int i = 0; i < n; i++) {
                    printf("\nEnter details for Process %d:\n", i + 1);
                    getDetails(&processes[i]);
                }
                break;

            case 2:
                printf("\nProcess Details:\n");
                for (int i = 0; i < n; i++) {
                    printf("\nDetails for Process %d:\n", i + 1);
                    displayDetails(processes[i]);
                }
                break;

            case 3:
                printf("Enter the process ID to search: ");
                scanf("%d", &pid);
                searchDetails(processes, n, pid);
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
