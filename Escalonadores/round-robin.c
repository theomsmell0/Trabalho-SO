#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
int waitingtime(int proc[], int n, int burst_time[], int wait_time[], int time_slice) {
    int remaining_time[n];
       
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }
    int tempo_global = 0; 
    while (1) {
        bool todos_terminaram = true;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                todos_terminaram = false; 
                
                if (remaining_time[i] > time_slice) {
                    tempo_global += time_slice;
                    remaining_time[i] -= time_slice;
                } 
                else {
                    tempo_global += remaining_time[i];
                    wait_time[i] = tempo_global - burst_time[i];
                    remaining_time[i] = 0; 
                }
            }
        }
        if (todos_terminaram) {
            break;
        }
    }
    return 0;
}
int turnaroundtime(int proc[], int n, int burst_time[], int wait_time[], int tat[]) {
   for (int i = 0; i < n ; i++) {
       tat[i] = burst_time[i] + wait_time[i];
   }
   return 0;
}
int avgtime(int proc[], int n, int burst_time[], int time_slice) {
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   
   waitingtime(proc, n, burst_time, wait_time, time_slice);
   
   turnaroundtime(proc, n, burst_time, wait_time, tat);
   
   printf("Processes  Burst   Waiting Turn around \n");
   for (int i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      printf(" %d\t  %d\t\t %d \t%d\n", proc[i], burst_time[i], wait_time[i], tat[i]);
   }
   printf("Average waiting time = %f\n", (float)total_wt / (float)n);
   printf("Average turn around time = %f\n", (float)total_tat / (float)n);
   return 0;
}
int main() {
   int n = 30;
   int proc[30];
   int burst_time[30];
   int tempos_opcoes[] = {5, 8, 12}; 
   
   srand(time(NULL));

   for (int i = 0; i < n; i++) {
       proc[i] = i + 1; 
       burst_time[i] = tempos_opcoes[rand() % 3]; 
   }

   int time_slice = 2; 
   avgtime(proc, n, burst_time, time_slice);
   return 0;
}
