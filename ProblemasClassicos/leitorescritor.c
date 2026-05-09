#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TAMANHO_BUFFER 5


int buffer[TAMANHO_BUFFER];
int indice_entrada = 0; // Onde o produtor vai colocar
int indice_saida = 0;   // De onde o consumidor vai tirar

sem_t espacos_vazios;   // Conta quantos espaços livres tem no buffer
sem_t espacos_cheios;   // Conta quantos itens tem prontos para consumo
pthread_mutex_t mutex;  // Cadeado para ninguem mexer no buffer ao mesmo tempo

/* Lógica do Produtor */
void* produtor(void* arg) {
    for (int i = 1; i <= 5; i++) {
        // --- ENTRADA ---
        sem_wait(&espacos_vazios);  // Pega uma "ficha" de espaço vazio. Se o buffer estiver lotado, ele dorme aqui.
        pthread_mutex_lock(&mutex); // Tranca o buffer só para ele

        // --- PRODUZINDO ---
        buffer[indice_entrada] = i;
        printf("[+] Produtor colocou o item %d na gaveta %d\n", i, indice_entrada);
        indice_entrada = (indice_entrada + 1) % TAMANHO_BUFFER; // Anda para a próxima gaveta
        
        // --- SAÍDA ---
        pthread_mutex_unlock(&mutex); // Destranca o buffer
        sem_post(&espacos_cheios);    // Avisa: "Criei mais um item! Tem mais um espaço cheio."
        
        sleep(1); // Simula o tempo de fabricação
    }
    return NULL;
}

/* Lógica do Consumidor */
void* consumidor(void* arg) {
    for (int i = 1; i <= 5; i++) {
        // --- ENTRADA ---
        sem_wait(&espacos_cheios);  // Pega uma "ficha" de item pronto. Se o buffer estiver vazio, ele dorme aqui esperando.
        pthread_mutex_lock(&mutex); // Tranca o buffer só para ele

        // --- CONSUMINDO ---
        int item = buffer[indice_saida];
        printf("[-] Consumidor retirou o item %d da gaveta %d\n", item, indice_saida);
        indice_saida = (indice_saida + 1) % TAMANHO_BUFFER; // Anda para a próxima gaveta

        // --- SAÍDA ---
        pthread_mutex_unlock(&mutex); // Destranca o buffer
        sem_post(&espacos_vazios);    // Avisa: "Tirei um item! Tem mais um espaço vazio agora."
        
        sleep(2); // Simula o tempo de consumo (um pouco mais lento que a produção)
    }
    return NULL;
}

/* Função Principal */
int main() {
    pthread_t thread_produtor, thread_consumidor;

    // Inicializando os cadeados e semáforos
    // Há 5 espaços vazios no início, e 0 espaços cheios.
    sem_init(&espacos_vazios, 0, TAMANHO_BUFFER); 
    sem_init(&espacos_cheios, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Iniciando as threads
    pthread_create(&thread_produtor, NULL, produtor, NULL);
    pthread_create(&thread_consumidor, NULL, consumidor, NULL);

    // Esperando as threads terminarem
    pthread_join(thread_produtor, NULL);
    pthread_join(thread_consumidor, NULL);

    return 0;
}
