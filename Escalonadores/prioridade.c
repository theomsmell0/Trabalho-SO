#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para encontrar o tempo de espera (Mantida do seu código)
int waitingtime(int proc[], int n, int burst_time[], int wait_time[]) {
   wait_time[0] = 0;
   for (int i = 1; i < n ; i++ ) {
       wait_time[i] = burst_time[i-1] + wait_time[i-1];
   }
   return 0;
}

// Função para calcular o turn around time (Mantida do seu código)
int turnaroundtime(int proc[], int n, int burst_time[], int wait_time[], int tat[]) {
   for (int i = 0; i < n ; i++) {
       tat[i] = burst_time[i] + wait_time[i];
   }
   return 0;
}

// Função auxiliar para trocar valores de posição
void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função principal de cálculo e exibição (Ajustada para receber a prioridade)
int avgtime(int proc[], int n, int burst_time[], int prioridade[]) {
   int wait_time[n], tat[n], total_wt = 0, total_tat = 0;
   
   waitingtime(proc, n, burst_time, wait_time);
   turnaroundtime(proc, n, burst_time, wait_time, tat);
   
   printf("Proc\tPrioridade\tBurst\tWaiting\tTurn around\n");
   printf("---------------------------------------------------\n");
   
   for (int i = 0; i < n; i++) {
      total_wt = total_wt + wait_time[i];
      total_tat = total_tat + tat[i];
      // Note que aqui usamos proc[i] para mostrar o ID original do processo, 
      // pois eles mudaram de ordem no vetor
      printf(" %d\t%d\t\t%d\t%d\t%d\n", proc[i], prioridade[i], burst_time[i], wait_time[i], tat[i]);
   }
   
   printf("\nAverage waiting time = %f\n", (float)total_wt / (float)n);
   printf("Average turn around time = %f\n", (float)total_tat / (float)n);
   return 0;
}

int main() {
   int n = 30; // Atualizado para 30 processos conforme o slide
   int proc[30];
   int burst_time[30];
   int prioridade[30];
   
   
   int tempos_opcoes[] = {5, 8, 12}; 
   
   
   srand(time(NULL));

   
   for (int i = 0; i < n; i++) {
       proc[i] = i + 1; // IDs de 1 a 30
       
       
       int indice_sorteio = rand() % 3; 
       burst_time[i] = tempos_opcoes[indice_sorteio];
       
       
       prioridade[i] = (rand() % 5) + 1; 
   }

   // 2. ETAPA DE ORDENAÇÃO (O Algoritmo de Prioridade)
   // Usamos um Bubble Sort simples para ordenar os vetores baseados na Prioridade
   for (int i = 0; i < n - 1; i++) {
       for (int j = 0; j < n - i - 1; j++) {
           
           // Se a prioridade atual for MAIOR que a próxima, eles trocam de lugar.
           // (Ex: Prioridade 3 vai para trás da Prioridade 1)
           if (prioridade[j] > prioridade[j + 1]) {
               
               // A regra de ouro dos vetores paralelos: trocou um, troca todos!
               trocar(&prioridade[j], &prioridade[j + 1]);
               trocar(&burst_time[j], &burst_time[j + 1]);
               trocar(&proc[j], &proc[j + 1]);
               
           }
       }
   }

   // 3. ETAPA DE CÁLCULO
   // Agora que os vetores estão ordenados por prioridade, basta rodar o cálculo normal
   printf("--- PRIORIDADE ---\n\n");
   avgtime(proc, n, burst_time, prioridade);

   return 0;
}