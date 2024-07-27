#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

// Structure to store thread-specific data
typedef struct {
    int *arr; // Pointer to the array of numbers
    int start; // Starting index for this thread
    int end; // Ending index for this thread
    int sum; // Sum calculated by this thread
} ThreadData;

// Function to be executed by each thread
void *sumThread(void *arg) {
    ThreadData *tdata = (ThreadData *)arg;
    tdata->sum = 0;
    for (int i = tdata->start; i < tdata->end; i++) {
        tdata->sum += tdata->arr[i];
    }
    pthread_exit(NULL);
}

int main() {
    int n;
    printf("Enter the number of elements (n > 1000): ");
    scanf("%d", &n);

    if (n <= 1000) {
        printf("Error: n must be greater than 1000.\n");
        return 1;
    }

    // Allocate memory for the array
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Error: Memory allocation failed.\n");
        return 1;
    }

    // Initialize the array with random numbers
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100; // Generate random numbers between 0 and 99
    }

    // Create an array of threads
    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];

    // Create threads and assign work
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].arr = arr;
        thread_data[i].start = (n / NUM_THREADS) * i;
        thread_data[i].end = (i == NUM_THREADS - 1) ? n : (n / NUM_THREADS) * (i + 1);
        if (pthread_create(&threads[i], NULL, sumThread, &thread_data[i]) != 0) {
            printf("Error: Thread creation failed.\n");
            free(arr);
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error: Thread join failed.\n");
            free(arr);
            return 1;
        }
    }

    // Calculate the total sum
    int totalSum = 0;
    for (int i = 0; i < NUM_THREADS; i++) {
        totalSum += thread_data[i].sum;
    }

    printf("Total sum of %d numbers: %d\n", n, totalSum);

    // Free allocated memory
    free(arr);

    return 0;
}



// lpthread: This flag tells the linker to search for and link the pthread library. 
// The -l option is used to specify libraries, and pthread is the name of the library.
// Example Compilation Command:
// gcc multithreads.c -lpthread -o multithreads