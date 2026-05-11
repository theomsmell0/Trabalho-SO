#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5  // Example buffer size

// Shared resource and state variables
int shared_resource = 0;
int readCount = 0;  // Number of readers currently reading

// Semaphores
sem_t mutex;        // Mutex for mutual exclusion (accessing readCount)
sem_t write;        // Semaphore for controlling access to the writer
sem_t readMutex;    // Semaphore for synchronizing the readCount

void *reader(void *param) {
    while (1) {
        sem_wait(&readMutex);      // Enter critical section to update readCount
        readCount++;               // Increment readCount
        if (readCount == 1) {
            sem_wait(&write);      // Block writers if it's the first reader
        }
        sem_post(&readMutex);      // Exit critical section

        // Critical section: Read the shared resource
        printf("Reader is reading: %d\n", shared_resource);

        sem_wait(&readMutex);      // Enter critical section to update readCount
        readCount--;               // Decrement readCount
        if (readCount == 0) {
            sem_post(&write);     // Last reader allows writer to proceed
        }
        sem_post(&readMutex);      // Exit critical section
    }
}

void *writer(void *param) {
    while (1) {
        sem_wait(&write);          // Wait until no readers or writers are active

        // Critical section: Write to the shared resource
        shared_resource++;
        printf("Writer is writing: %d\n", shared_resource);

        sem_post(&write);          // Release the write lock
    }
}

int main() {
    pthread_t readerThread, writerThread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&write, 0, 1);
    sem_init(&readMutex, 0, 1);

    // Create reader and writer threads
    pthread_create(&readerThread, NULL, reader, NULL);
    pthread_create(&writerThread, NULL, writer, NULL);

    // Join threads
    pthread_join(readerThread, NULL);
    pthread_join(writerThread, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write);
    sem_destroy(&readMutex);

    return 0;
}