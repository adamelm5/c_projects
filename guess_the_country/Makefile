# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c99 -g

# Fichiers sources
SRCS = src/devine.c src/fichiers.c src/manip.c

# Fichiers objets (générés à partir des fichiers sources)
OBJS = $(SRCS:.c=.o)

# Nom de l'exécutable final
TARGET = play

# Règle par défaut
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Règle pour compiler les fichiers source en fichiers objet
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour réinstaller (nettoyer puis recompiler)
reinstall: clean all

# Indique que les règles "all", "clean" et "reinstall" ne sont pas des fichiers
.PHONY: all clean reinstall