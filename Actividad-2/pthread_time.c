#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>


void *thread_function(void *arg) {
    struct timeval start, end;
    long seconds, useconds;
    gettimeofday(&start, NULL);  // Time before thread starts

    // Simulate some task
    // sleep(1);  // Example: simulate the execution of a thread

    gettimeofday(&end, NULL);  // Time after thread execution starts
    seconds = end.tv_sec - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    printf("Thread: Time elapsed (pthread_create) = %ld seconds and %ld microseconds\n", seconds, useconds);

    return NULL;
}

void measure_time_pthread(int n) {
    struct timeval start, end;
    long seconds, useconds;
    pthread_t thread_id;

    for (int i = 0; i < n; i++) {
        gettimeofday(&start, NULL);  // Time before thread creation
        
        pthread_create(&thread_id, NULL, thread_function, NULL);
        pthread_join(thread_id, NULL);  // Wait for thread to finish
        
        gettimeofday(&end, NULL);  // Time after thread starts
        seconds = end.tv_sec - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
        printf("Thread %d: Time elapsed (pthread_create) = %ld seconds and %ld microseconds\n", i+1, seconds, useconds);
    }
}

int main() {
    int n;
    printf("Enter the number of threads to create: ");
    scanf("%d", &n);
    measure_time_pthread(n);
    return 0;
}
