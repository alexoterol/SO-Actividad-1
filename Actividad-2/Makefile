CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lpthread

# Archivos fuente y ejecutables
SRC_FORK = fork_time.c
SRC_PTHREAD = pthread_time.c
EXEC_FORK = fork_time
EXEC_PTHREAD = pthread_time

# Compilación de ambos programas
all: $(EXEC_FORK) $(EXEC_PTHREAD)

# Compilar el programa con fork
$(EXEC_FORK): $(SRC_FORK)
	$(CC) $(CFLAGS) -o $(EXEC_FORK) $(SRC_FORK)

# Compilar el programa con pthread
$(EXEC_PTHREAD): $(SRC_PTHREAD)
	$(CC) $(CFLAGS) -o $(EXEC_PTHREAD) $(SRC_PTHREAD) $(LDFLAGS)

# Limpieza de archivos generados
clean:
	rm -f $(EXEC_FORK) $(EXEC_PTHREAD)

# Ejecutar ambos programas
run: $(EXEC_FORK) $(EXEC_PTHREAD)
	./$(EXEC_FORK)
	./$(EXEC_PTHREAD)

.PHONY: all clean run
