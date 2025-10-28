#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1

int main() {
    char command[256];
    pid_t pid;
    int fd[2];

    while (1) {
        printf("Ingrese un comando: ");
        fgets(command, sizeof(command), stdin);

        // Elimina el salto de línea
        command[strcspn(command, "\n")] = 0;

        if (strncmp(command, "exit", 4) == 0) {
            break;  // Salir si el comando es "exit"
        }

        pipe(fd);  // Crear un pipe

        pid = fork();  // Crear un proceso hijo

        if (pid == 0) {  // Este es el proceso hijo
            close(fd[0]);  // Cierra el extremo de lectura del pipe
            dup2(fd[1], STDOUT);  // Redirige stdout al pipe
            close(fd[1]);  // Cierra el descriptor original del pipe

            // Ejecutar el comando con execvp
            char *args[] = {"/bin/sh", "-c", command, NULL};
            execvp(args[0], args);  // Ejecuta el comando
            perror("execvp falló");
            exit(1);  // Termina el proceso hijo si execvp falla
        } else if (pid > 0) {  // Este es el proceso padre
            close(fd[1]);  // Cierra el extremo de escritura del pipe
            waitpid(pid, NULL, 0);  // Espera a que termine el proceso hijo
        } else {
            perror("fork falló");
            exit(1);  // En caso de error en fork()
        }
    }

    return 0;
}
