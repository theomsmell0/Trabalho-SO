#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t wrt;                // Cadeado dos escritores
pthread_mutex_t mutex;    // Cadeado do contador de leitores
int num_leitores = 0;     // Quantos leitores estão na sala?

/* Lógica do Leitor */
void* leitor(void* arg) {
    int id = *(int*)arg;
  
    pthread_mutex_lock(&mutex);   // Protege o contador
    num_leitores++;               // Entrou um leitor
    if (num_leitores == 1) {
        sem_wait(&wrt);           // Se for o 1º leitor, tranca a porta para os escritores
    }
    pthread_mutex_unlock(&mutex); // Libera o contador para o próximo leitor

    
    printf("Leitor %d esta lendo...\n", id);
    sleep(1); 

    
    pthread_mutex_lock(&mutex);   // Protege o contador
    num_leitores--;               // Saiu um leitor
    if (num_leitores == 0) {
        sem_post(&wrt);           // Se for o último a sair, destranca a porta para os escritores
    }
    pthread_mutex_unlock(&mutex); // Libera o contador

    return NULL;
}


void* escritor(void* arg) {
    int id = *(int*)arg;

   
    sem_wait(&wrt); // O escritor tranca a porta geral. Ninguém mais entra.

   
    printf("Escritor %d esta modificando os dados...\n", id);
    sleep(2);

  
    sem_post(&wrt); // O escritor destranca a porta geral e vai embora.

    return NULL;
}


int main() {
    // 1. Prepara as variáveis
    pthread_t thread_leitor1, thread_leitor2, thread_escritor;
    int id1 = 1, id2 = 2, id3 = 1;

    // 2. Inicializa os cadeados (semáforo e mutex)
    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // 3. Inicia as threads uma a uma manualmente
    pthread_create(&thread_leitor1, NULL, leitor, &id1);
    pthread_create(&thread_escritor, NULL, escritor, &id3);
    pthread_create(&thread_leitor2, NULL, leitor, &id2);

    // 4. Espera as três terminarem
    pthread_join(thread_leitor1, NULL);
    pthread_join(thread_escritor, NULL);
    pthread_join(thread_leitor2, NULL);

    return 0;
}
