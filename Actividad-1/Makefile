# Definir variables
CC = gcc
CFLAGS = -Wall -std=c99
EXEC = main

# Regla por defecto para compilar el ejecutable
all: $(EXEC)

# Regla para compilar el ejecutable 'shell'
$(EXEC): main.c
	$(CC) $(CFLAGS) -o $(EXEC) main.c

# Limpiar los archivos generados (ejecutables)
clean:
	rm -f $(EXEC)

# Ejecutar el programa
run: $(EXEC)
	./$(EXEC)

.PHONY: all clean run
