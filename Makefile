# définition des cibles particulières
.PHONY: clean, mrproper
# désactivation des règles implicites
.SUFFIXES:
# définition des variables
CC = gcc
CFLAGS = -W -Wall

# Le nom de l’exécutable à fabriquer
EXE=snake

# all
all: $(EXE)

$(EXE): grid.o llist.o snake.o
	 $(CC) $^ $(CFLAGS) -o $@

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# clean
clean:
	rm -rf *.bak rm -rf *.o rm rm *~
# mrproper
mrproper: clean
	rm -rf $(EXE) 