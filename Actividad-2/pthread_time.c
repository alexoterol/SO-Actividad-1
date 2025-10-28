#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>


void *thread_function(void *arg) {
    struct timeval start, end;
    gettimeofday(&start, NULL);  // Tiempo antes de la ejecucion

    int calcSum = 2+2;  // Ejecutar un comando

    gettimeofday(&end, NULL);  // Tiempo despues de la ejecucion
    printf("Resultado: %d, ", calcSum);

    return NULL;
}

void measure_time_pthread(int n) {
    struct timeval start, end;
    long seconds, useconds;
    pthread_t thread_id;

    for (int i = 0; i < n; i++) {
        gettimeofday(&start, NULL);  // Tiempo antes de la creacion del hilo
        
        pthread_create(&thread_id, NULL, thread_function, NULL);
        pthread_join(thread_id, NULL);  // Esperar a los hilos a que terminen
        
        gettimeofday(&end, NULL);  // Tiempo despues de terminar ejecuciones
        seconds = end.tv_sec - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;
        printf("Hilo %d: Tiempo transcurrido (pthread_create) = %ld segundos y %ld microsegundos\n", i+1, seconds, useconds);
    }
}

int main() {
    int n;
    printf("Ingresa el numero de hilos: ");
    scanf("%d", &n);
    measure_time_pthread(n);
    return 0;
}
