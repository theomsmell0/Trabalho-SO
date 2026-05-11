#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// troca de valores na memória
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
// Function to find the waiting time for all processes (Inalterada)
int waitingtime(int proc[], int n, int burst_time[], int wait_time[]) {
   wait_time[0] = 0;
   for (int i = 1; i < n ; i++ )
       wait_time[i] = burst_time[i-1] + wait_time[i-1] ;
   return 0;
}

// Function to calculate turn around time (Inalterada)
int turnaroundtime( int proc[], int n, int burst_time[], int wait_time[], int tat[]) {
   int i;
   for ( i = 0; i < n ; i++)
       tat[i] = burst_time[i] + wait_time[i];
   return 0;
}

//Function to calculate average time
int avgtime( int proc[], int n, int burst_time[]) {
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   int i;
   waitingtime(proc, n, burst_time, wait_time);
   turnaroundtime(proc, n, burst_time, wait_time, tat);
   
   printf("Proc\tBurst\tWaiting\tTurn around\n");
   printf("-----------------------------------\n");
   
   for ( i=0; i<n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      printf(" %d\t%d\t%d\t%d\n", proc[i], burst_time[i], wait_time[i], tat[i]);
   }
   
   printf("\nAverage waiting time = %f\n", (float)total_wt / (float)n);
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



   for (int i = 0; i < n - 1; i++) {
       for (int j = 0; j < n - i - 1; j++) {
           if (burst_time[j] > burst_time[j + 1]) {
               trocar(&burst_time[j], &burst_time[j + 1]);

               trocar(&proc[j], &proc[j + 1]);
           }
       }
   }
   
   printf("---  SJF  ---\n\n");
   avgtime(proc, n, burst_time);
   
   return 0;
}
