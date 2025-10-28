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
        gettimeofday(&start, NULL);  // Tiempo antes de iniciar fork
        
        pid = fork();
        
        if (pid == 0) { // Hijo
            gettimeofday(&end, NULL);  // Tiempo antes de la primera instruccion
            int calcSum = 2+2; // Ejecutar un comando 
            seconds = end.tv_sec - start.tv_sec;
            useconds = end.tv_usec - start.tv_usec;
            printf("Resultado: %d, Proceso %d: Tiempo transcurrido (fork) = %ld segundos y %ld microsegundos.\n", calcSum, i+1, seconds, useconds);
            exit(0);
        }
        else {
            wait(NULL);  // Esperar que proceso hijo termine
        }
    }
}

int main() {
    int n;
    printf("Ingresar numero de procesos: ");
    scanf("%d", &n);
    measure_time_fork(n);
    return 0;
}
