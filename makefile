# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -Iauxiliares -Igrafos
TARGET = grafo
SRCS = main.c \
	   grafos/lista_adj.c grafos/matriz_adj.c \
	   auxiliares/auxiliares.c auxiliares/pilha.c \
	   auxiliares/fila.c auxiliares/heap_bin.c
OBJS = $(SRCS:.c=.o)

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilação de cada arquivo .c
%.o: %.c grafo.h
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJS) $(TARGET)

# Regra para rodar o programa
run: $(TARGET)
	./$(TARGET)

# Regra de ajuda
help:
	@echo "Comandos disponíveis:"
	@echo "  make        - Compila o programa."
	@echo "  make run    - Compila e executa o programa."
	@echo "  make clean  - Remove arquivos objeto e executáveis."
