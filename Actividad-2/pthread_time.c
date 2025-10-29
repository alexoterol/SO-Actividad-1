#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

void *thread_function(void *arg) {
    struct timeval *end = (struct timeval *)arg;
    gettimeofday(end, NULL);  // Tiempo después del cambio de contexto
    int calcSum = 2 + 2;
    printf("Resultado: %d, ", calcSum);
    return NULL;
}

void measure_time_pthread(int n) {
    struct timeval start, end;
    long seconds, useconds;
    pthread_t thread_id;
    long total_seconds = 0, total_useconds = 0;

    for (int i = 0; i < n; i++) {
        gettimeofday(&start, NULL);  // Antes de crear el hilo
        
        pthread_create(&thread_id, NULL, thread_function, &end);
        pthread_join(thread_id, NULL); // Esperar a que termine

        seconds = end.tv_sec - start.tv_sec;
        useconds = end.tv_usec - start.tv_usec;

        total_seconds += seconds;
        total_useconds += useconds;

        printf("Hilo %d: Tiempo transcurrido (pthread_create) = %ld segundos y %ld microsegundos\n",
               i + 1, seconds, useconds);
    }

    // Calcular el promedio
    long avg_seconds = total_seconds / n;
    long avg_useconds = total_useconds / n;

    // Ajustar si los microsegundos superan 1 segundo
    if (avg_useconds >= 1000000) {
        avg_seconds += avg_useconds / 1000000;
        avg_useconds = avg_useconds % 1000000;
    }

    printf("\nPromedio: %ld segundos y %ld microsegundos\n", avg_seconds, avg_useconds);
}

int main() {
    int n;
    printf("Ingresa el número de hilos: ");
    scanf("%d", &n);
    measure_time_pthread(n);
    return 0;
}
