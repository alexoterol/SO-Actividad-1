#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

void measure_time_fork(int n) {
    struct timeval start, end;
    long seconds, useconds;
    pid_t pid;
    long total_seconds = 0, total_useconds = 0;

    for (int i = 0; i < n; i++) {
        // Crear un nuevo pipe para cada hijo
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(1);
        }

        gettimeofday(&start, NULL);  // Tiempo antes de iniciar fork
        
        pid = fork();
        
        if (pid == 0) { // Proceso hijo
            gettimeofday(&end, NULL);  // Tiempo después del cambio de contexto
            seconds = end.tv_sec - start.tv_sec;
            useconds = end.tv_usec - start.tv_usec;

            // Cerrar el descriptor de lectura en el hijo, porque solo escribirá
            close(pipefd[0]);

            // Escribir los tiempos en el pipe
            write(pipefd[1], &seconds, sizeof(seconds));
            write(pipefd[1], &useconds, sizeof(useconds));

            // Información del proceso hijo
            printf("Proceso %d: Tiempo transcurrido (fork) = %ld segundos y %ld microsegundos.\n", i + 1, seconds, useconds);

            close(pipefd[1]);  // Cerrar después de escribir
            exit(0);  // Termina el proceso hijo
        }
        else {  // Proceso padre
            // Cerrar el descriptor de escritura en el padre, porque solo leerá
            close(pipefd[1]);

            wait(NULL);  // Esperar que el proceso hijo termine

            // Leer los tiempos del proceso hijo desde la pipe
            read(pipefd[0], &seconds, sizeof(seconds));
            read(pipefd[0], &useconds, sizeof(useconds));

            total_seconds += seconds;
            total_useconds += useconds;

            // Cerrar el descriptor de lectura después de leer
            close(pipefd[0]);
        }
    }

    // Calcular el promedio de tiempos
    long avg_seconds = total_seconds / n;
    long avg_useconds = total_useconds / n;

    // Ajuste si los microsegundos superan 1 segundo
    if (avg_useconds >= 1000000) {
        avg_seconds += avg_useconds / 1000000;
        avg_useconds = avg_useconds % 1000000;
    }

    // Imprimir el promedio de los tiempos de cambio de contexto
    printf("\nPromedio de tiempos de cambio de contexto: %ld segundos y %ld microsegundos\n", avg_seconds, avg_useconds);
}

int main() {
    int n;
    printf("Ingresar número de procesos: ");
    scanf("%d", &n);
    measure_time_fork(n);
    return 0;
}
