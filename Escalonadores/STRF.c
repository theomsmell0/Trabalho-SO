#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

int waitingtime(int proc[], int n, int burst_time[], int wait_time[], int arrival_time[]) {
    int rt[n];
    
    for (int i = 0; i < n; i++)
        rt[i] = burst_time[i];

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    while (complete != n) {
      
        for (int j = 0; j < n; j++) {
            if ((arrival_time[j] <= t) && (rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false) {
            t++;
            continue;
        }
        rt[shortest]--;
        minm = rt[shortest];
        
        if (minm == 0)
            minm = INT_MAX;

        
        if (rt[shortest] == 0) {
            complete++;
            check = false;
            finish_time = t + 1;
            wait_time[shortest] = finish_time - burst_time[shortest] - arrival_time[shortest];
            
            if (wait_time[shortest] < 0)
                wait_time[shortest] = 0;
        }
        t++;
    }
    return 0;
}

int turnaroundtime(int proc[], int n, int burst_time[], int wait_time[], int tat[]) {
    for (int i = 0; i < n; i++)
        tat[i] = burst_time[i] + wait_time[i];
    return 0;
}
int avgtime(int proc[], int n, int burst_time[], int arrival_time[]) {
    int wait_time[n], tat[n], total_wt = 0, total_tat = 0;

    waitingtime(proc, n, burst_time, wait_time, arrival_time);
    turnaroundtime(proc, n, burst_time, wait_time, tat);

    printf("Proc\tArrive\t\tBurst\t\tWait\t\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        total_wt = total_wt + wait_time[i];
        total_tat = total_tat + tat[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i], arrival_time[i], burst_time[i], wait_time[i], tat[i]);
    }
    printf("\nTempo medio de espera = %f\n", (float)total_wt / (float)n);
    printf("Tempo medio de turnaround = %f\n", (float)total_tat / (float)n);
    return 0;
}

int main() {
    srand(time(NULL));
    
    int n = 30;
    int proc[n];
    int burst_time[n];
    int arrival_time[n]
    int burst_options[] = {5, 8, 12};

    for (int i = 0; i < n; i++) {
        proc[i] = i + 1;
        burst_time[i] = burst_options[rand() % 3];
        arrival_time[i] = rand() % 50; 
    }

    avgtime(proc, n, burst_time, arrival_time);
    
    return 0;
}
