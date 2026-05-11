#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define CADEIRAS_ESPERA 3

/* Variáveis Globais */
sem_t sem_clientes;      // Avisa o barbeiro que há clientes esperando
sem_t sem_barbeiro;      // Avisa o cliente que o barbeiro está pronto
pthread_mutex_t mutex;   // Cadeado para proteger a contagem de cadeiras

int cadeiras_ocupadas = 0;

/* Lógica do Barbeiro */
void* barbeiro(void* arg) {
    while (1) {
        // 1. O barbeiro tenta pegar um cliente. Se não tiver (sem_clientes == 0), ele DORME aqui.
        sem_wait(&sem_clientes); 
        
        // 2. Um cliente acordou o barbeiro! Vamos tirar ele da cadeira de espera.
        pthread_mutex_lock(&mutex);
        cadeiras_ocupadas--; 
        printf("[Barbeiro] Chamou um cliente. Cadeiras de espera ocupadas: %d\n", cadeiras_ocupadas);
        pthread_mutex_unlock(&mutex);
        
        // 3. Avisa ao cliente específico que a cadeira de corte está pronta para ele.
        sem_post(&sem_barbeiro); 
        
        // 4. Corta o cabelo
        printf("[Barbeiro] Cortando o cabelo...\n\n");
        sleep(2); // Tempo que leva o corte
    }
    return NULL;
}

/* Lógica do Cliente */
void* cliente(void* arg) {
    int id = *(int*)arg;
    
    // 1. O cliente chega e olha para as cadeiras
    pthread_mutex_lock(&mutex);
    
    if (cadeiras_ocupadas < CADEIRAS_ESPERA) {
        // 2. Tem lugar! Ele senta.
        cadeiras_ocupadas++;
        printf("[Cliente %d] Entrou e sentou na espera. Cadeiras ocupadas: %d\n", id, cadeiras_ocupadas);
        
        // 3. Ele dá um grito: "Tem cliente na loja!" (Isso acorda o barbeiro se ele estiver dormindo)
        sem_post(&sem_clientes); 
        pthread_mutex_unlock(&mutex); // Libera a porta da barbearia para outros olharem as cadeiras
        
        // 4. Fica esperando o barbeiro chamar para a cadeira de corte
        sem_wait(&sem_barbeiro); 
        printf("[Cliente %d] Teve o cabelo cortado e foi embora feliz.\n", id);
        
    } else {
        // 2 (Alternativo). Não tem lugar.
        pthread_mutex_unlock(&mutex); // Libera a porta
        printf("[Cliente %d] Barbearia lotada! Foi embora frustrado.\n", id);
    }
    return NULL;
}

/* Função Principal */
int main() {
    pthread_t thread_barbeiro, thread_clientes[5];
    int ids_clientes[5] = {1, 2, 3, 4, 5};

    // Inicializando semáforos e mutex
    sem_init(&sem_clientes, 0, 0); // Começa com 0 clientes
    sem_init(&sem_barbeiro, 0, 0); // Barbeiro começa não estando pronto
    pthread_mutex_init(&mutex, NULL);

    // Cria o barbeiro (ele vai direto dormir, pois não há clientes)
    pthread_create(&thread_barbeiro, NULL, barbeiro, NULL);

    // Cria 5 clientes chegando praticamente ao mesmo tempo
    for (int i = 0; i < 5; i++) {
        pthread_create(&thread_clientes[i], NULL, cliente, &ids_clientes[i]);
        sleep(1); // Um pequeno intervalo entre a chegada de cada um
    }

    // Espera os clientes terminarem
    for (int i = 0; i < 5; i++) {
        pthread_join(thread_clientes[i], NULL);
    }

    return 0;
}
