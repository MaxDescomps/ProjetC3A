EXT = .bin
INCLUDE = $(addprefix -I , include)
GEN = $(BINDIR)jeu$(EXT)
LDFLAGS = -lncurses # Options d'édition de liens.
DIRMAKE = mkdirs.sh
rm = rm -f obj/*.o

CC = gcc # Nom du compilateur.
CFLAGS =-Wall $(INCLUDE) # Options de compilation.
ODIR = obj/# Répertoire des fichiers objets
SRC = src/# Répertoire des fichiers sources
BINDIR = bin/# Répertoire des exécutables
OBJ = $(addsuffix .o, $(addprefix $(ODIR), main affichage carte coord erreur input inventaire menu mob perso liste tir entite coffre item jeu))

all : makedir $(GEN) # Génération de tout les fichiers

bin : $(BINDIR)jeu$(EXT) # Génération executable

#programme principal
$(BINDIR)jeu$(EXT) : $(OBJ)
	$(CC) $^ -o $@  $(LDFLAGS) 
	
# Compilation de tout les fichiers source
$(ODIR)%.o : $(SRC)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

#options de suppression
.PHONY: clean mrproper makedir

clean:
	@$(rm) 
	@echo "Cleanup complete!"

mrproper: clean
	@$(rm) $(GEN)
	@echo "Executable removed!"

makedir :
	@chmod u+x $(DIRMAKE)
	@./$(DIRMAKE)