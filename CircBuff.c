#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>    // For pthread functions (threading, mutexes)
#include <semaphore.h>  // For semaphore functions (synchronization)
#include <unistd.h>     // For sleep() (simulating work)

#define BUFFER_SIZE 5  // Define the size of the circular buffer

// Circular buffer structure
typedef struct {
    int buffer[BUFFER_SIZE];   // Buffer to hold the data
    int in;                    // Index for the producer to insert data
    int out;                   // Index for the consumer to remove data
    sem_t empty;               // Semaphore for empty slots in the buffer (initially full)
    sem_t full;                // Semaphore for full slots in the buffer (initially empty)
    pthread_mutex_t mutex;     // Mutex for mutual exclusion when accessing the buffer
} CircularBuffer;

// Initialize the circular buffer
CircularBuffer circBuffer = { .in = 0, .out = 0 }; // Set in and out indexes to 0 initially

// Function to initialize the circular buffer
void initBuffer(CircularBuffer* cb) {
    sem_init(&cb->empty, 0, BUFFER_SIZE);  // Set the initial value of empty slots to BUFFER_SIZE
    sem_init(&cb->full, 0, 0);             // Set the initial value of full slots to 0
    pthread_mutex_init(&cb->mutex, NULL);  // Initialize the mutex for mutual exclusion
}

// Producer function - adds data to the circular buffer
void* producer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Produce 10 items
        item = i; // Set the produced item

        // Wait if the buffer is full (i.e., no empty slots)
        sem_wait(&circBuffer.empty);

        // Lock the buffer before inserting data to avoid race conditions
        pthread_mutex_lock(&circBuffer.mutex);

        // Insert the item into the buffer at the 'in' position
        circBuffer.buffer[circBuffer.in] = item;
        printf("Produced: %d\n", item);

        // Move the 'in' pointer to the next slot (circular behavior)
        circBuffer.in = (circBuffer.in + 1) % BUFFER_SIZE;

        // Unlock the mutex after modifying the buffer
        pthread_mutex_unlock(&circBuffer.mutex);

        // Signal that there is now a new full slot (item in the buffer)
        sem_post(&circBuffer.full);

        // Simulate work by sleeping for 1 second
        sleep(1);
    }
    return NULL;  // End of producer thread
}

// Consumer function - removes data from the circular buffer
void* consumer(void* arg) {
    int item;
    for (int i = 0; i < 10; i++) {  // Consume 10 items
        // Wait if the buffer is empty (i.e., no full slots)
        sem_wait(&circBuffer.full);

        // Lock the buffer before removing data to avoid race conditions
        pthread_mutex_lock(&circBuffer.mutex);

        // Remove an item from the buffer at the 'out' position
        item = circBuffer.buffer[circBuffer.out];
        printf("Consumed: %d\n", item);

        // Move the 'out' pointer to the next slot (circular behavior)
        circBuffer.out = (circBuffer.out + 1) % BUFFER_SIZE;

        // Unlock the mutex after modifying the buffer
        pthread_mutex_unlock(&circBuffer.mutex);

        // Signal that there is now a new empty slot (space available in the buffer)
        sem_post(&circBuffer.empty);

        // Simulate work by sleeping for 2 seconds
        sleep(2);
    }
    return NULL;  // End of consumer thread
}

int main() {
    pthread_t producerThread, consumerThread;

    // Initialize the circular buffer
    initBuffer(&circBuffer);

    // Create the producer and consumer threads
    // Thread creation takes the following arguments:
    // 1. Pointer to thread handle
    // 2. Thread attributes (NULL for default)
    // 3. The function to be executed by the thread
    // 4. Argument to be passed to the function (NULL in this case)
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for both threads to finish execution (joining threads)
    // The parent thread waits for the producer and consumer threads to complete.
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Clean up the semaphores and mutex after they are no longer needed
    sem_destroy(&circBuffer.empty);
    sem_destroy(&circBuffer.full);
    pthread_mutex_destroy(&circBuffer.mutex);

    return 0;
}
