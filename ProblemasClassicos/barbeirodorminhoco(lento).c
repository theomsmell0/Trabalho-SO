#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CADEIRAS_ESPERA 3

sem_t sem_clientes;      
sem_t sem_barbeiro;      
pthread_mutex_t mutex;   

int cadeiras_ocupadas = 0;

void* barbeiro(void* arg) {
    while (1) {
        // Adicionada a indicação clara de que ele vai dormir ANTES de travar no semáforo
        printf("[Barbeiro] A barbearia esta vazia. Indo dormir na cadeira zZz...\n");
        
        sem_wait(&sem_clientes); // Dorme aqui se não tiver ninguém
        
        pthread_mutex_lock(&mutex);
        cadeiras_ocupadas--; 
        printf("[Barbeiro] Acordou/Chamou cliente! Cadeiras de espera ocupadas: %d\n", cadeiras_ocupadas);
        pthread_mutex_unlock(&mutex);
        
        sem_post(&sem_barbeiro); 
        
        printf("[Barbeiro] Cortando o cabelo (vai demorar)...\n\n");
        sleep(3); // Aumentei o tempo de corte para 3 segundos para gerar fila
    }
    return NULL;
}

void* cliente(void* arg) {
    int id = *(int*)arg;
    
    pthread_mutex_lock(&mutex);
    
    if (cadeiras_ocupadas < CADEIRAS_ESPERA) {
        cadeiras_ocupadas++;
        printf("[Cliente %d] Entrou e sentou na espera. Cadeiras ocupadas: %d\n", id, cadeiras_ocupadas);
        
        sem_post(&sem_clientes); 
        pthread_mutex_unlock(&mutex); 
        
        sem_wait(&sem_barbeiro); 
        printf("[Cliente %d] Teve o cabelo cortado e foi embora.\n", id);
        
    } else {
        // Quando a cadeira_ocupadas bater 3, ele cai aqui direto.
        pthread_mutex_unlock(&mutex);
        printf("[Cliente %d] OLHOU A BARBEARIA LOTADA E FOI EMBORA INSATISFEITO!\n", id);
    }
    return NULL;
}

int main() {
    pthread_t thread_barbeiro, thread_clientes[8];
    int ids_clientes[8] = {1, 2, 3, 4, 5, 6, 7, 8}; // Aumentei para 8 clientes

    sem_init(&sem_clientes, 0, 0); 
    sem_init(&sem_barbeiro, 0, 0); 
    pthread_mutex_init(&mutex, NULL);

    // O barbeiro entra primeiro, vê que não tem ninguém e vai dormir
    pthread_create(&thread_barbeiro, NULL, barbeiro, NULL);
    sleep(1); // Dá 1 segundo para você ler no terminal que ele foi dormir

    // Manda 8 clientes entrarem em um intervalo muito rápido (0.5 segundos)
    for (int i = 0; i < 8; i++) {
        pthread_create(&thread_clientes[i], NULL, cliente, &ids_clientes[i]);
        usleep(500000); // usleep pausa em microssegundos (500000 = meio segundo)
    }

    for (int i = 0; i < 8; i++) {
        pthread_join(thread_clientes[i], NULL);
    }

    return 0;
}
