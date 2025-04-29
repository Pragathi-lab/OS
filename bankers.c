#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m, i, j, k;
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int finish[MAX_PROCESSES] = {0};
    int safeSequence[MAX_PROCESSES];
    int count = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the maximum matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate the need matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                bool canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }
                    safeSequence[count++] = i;
                    finish[i] = 1;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state!\n");
            return 0;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (i = 0; i < n; i++) {
        printf("P%d", safeSequence[i]);
        if (i != n-1) printf(" -> ");
    }
    printf("\n");

    return 0;
}
