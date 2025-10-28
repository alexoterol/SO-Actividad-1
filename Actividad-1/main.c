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
        // Imprimir mensaje para ingresar el comando
        printf("Ingrese un comando: ");
        // Leer el comando del usuario
        fgets(command, sizeof(command), stdin);
        
        // Eliminar el salto de línea que fgets captura
        command[strcspn(command, "\n")] = 0;

        // Si el usuario escribe "exit", salir del bucle
        if (strncmp(command, "exit", 4) == 0) {
            break;  // Termina el ciclo si el comando es "exit"
        }

        // Crear el pipe
        if (pipe(fd) == -1) {
            perror("Pipe failed");
            return 1;
        }

        // Crear el proceso hijo
        pid = fork();  // Crear un proceso hijo
        
        if (pid == 0) {  // Este es el proceso hijo
            close(fd[0]);  // Cierra la entrada estándar del hijo
            dup2(fd[1], STDOUT);  // Redirige la salida estándar al pipe
            close(fd[1]);  // Cierra el descriptor de escritura del pipe

            // Ejecutar el comando con execvp
            char *args[] = {"/bin/cat", "-c", command, NULL};
            execvp(args[0], args);  // Ejecuta el comando
            perror("execvp failed");  // Si execvp falla, mostrar error
            exit(0);  // Termina el proceso hijo
        } else if (pid > 0) {  // Este es el proceso padre
            close(fd[1]);  // Cierra la salida estándar del padre
            dup2(fd[0], STDIN);  // Redirige la entrada estándar al pipe
            close(fd[0]);  // Cierra el descriptor de lectura del pipe

            // Espera a que el proceso hijo termine
            waitpid(pid, NULL, 0);  // Espera a que termine el proceso hijo
        } else {
            perror("Fork failed");
            return 1;  // En caso de que fork falle
        }
    }

    return 0;  // Termina el programa
}
