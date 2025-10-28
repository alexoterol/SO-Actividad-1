#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

void measure_time_fork(int n) {
    struct timeval start, end;
    long seconds, useconds;
    pid_t pid;

    for (int i = 0; i < n; i++) {
        gettimeofday(&start, NULL);  // Time before fork
        
        pid = fork();
        
        if (pid == 0) {
            // Child process
            gettimeofday(&end, NULL);  // Time after the first instruction of the child
            // Example: simulate the execution of a thread 
            seconds = end.tv_sec - start.tv_sec;
            useconds = end.tv_usec - start.tv_usec;
            printf("Process %d: Time elapsed (fork) = %ld seconds and %ld microseconds\n", i+1, seconds, useconds);
            exit(0);
        }
        else {
            wait(NULL);  // Wait for the child to finish
        }
    }
}

int main() {
    int n;
    printf("Enter the number of processes to create: ");
    scanf("%d", &n);
    measure_time_fork(n);
    return 0;
}
