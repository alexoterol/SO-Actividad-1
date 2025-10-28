#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h> // Libreria necesaria para waitpid(PID,STATUS,FLAGS)

#define STDIN 0
#define STDOUT 1

int main() {
    char command[256];
    pid_t pid;
    int fd[2];
    
    while (1) {
        printf("(◣_◢)>: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Busca en command el \n y reemplazalo por \0

        if (strncmp(command, "exit", 4) == 0) {
            break;  // Salir del programa si se escribe exit
        }

        pipe(fd);  // Crear pipe
        pid = fork();  // Crear proceso hijo
        
        if (pid == 0) {  // Proceso HIJO
            close(STDIN);
            dup(fd[0]);  // Redirige stdin al pipe
            close(fd[0]); // Cierra file descriptor no usado de lectura
            close(fd[1]); // Hijo no escribe al pipe

            // Ejecutar comando con execvp
            char *args[] = {"/bin/sh", "-c", command, NULL}; // Ruta del comando, ejecutar lo siguiente como comando, variable ingresada por usuario, valor final.
            execvp(args[0], args);  // Ejecuta el comando Shell para que lo interprete y ejecute, argumentos que pasan al programa ejecutable.
            exit(0);  // Terminar proceso
        } else {  // Proceso PADRE
            close(fd[1]); // Padre no escribe al pipe
            char buffer[1000]; // Variable para almacenar los datos leidos desde el pipe 
            ssize_t bytesRead; // Almacenar numero de bytes que se leen del pipe

            while ((bytesRead = read(fd[0], buffer, sizeof(buffer)-1)) > 0 ){ // Leer lo que haya en el pipe y almacenarlo en el buffer hasta que haya solo un espacio sobrante.
                buffer[bytesRead] = '\0'; // En el ultimo index del buffer cargado con la info, reemplazarlo por \0
                write(STDOUT, buffer, bytesRead); //Escribir en la terminal la informacion almacenada en el buffer y asegurate que el mensaje tiene bytesRead de longitud.
            }
            close(fd[0]); // Cerrar el extremo de lectura
            waitpid(pid, NULL, 0);  // Espera la terminacion del proceso hijo
        }
    }

    return 0;
}

