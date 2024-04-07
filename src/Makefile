# ======================
# Opcions d'optimització
# ======================
OPT=-g -Wall
#OPT=-O3 -Wall

tot : dibfr

# ========
# Utilitat
# ========
dibfr : dibfr.o nwtfr.o
	gcc -o dibfr $(OPT) dibfr.o nwtfr.o -lm
dibfr.o : dibfr.c
	gcc -c $(OPT) dibfr.c

# ==========
# Biblioteca
# ==========
nwtfr.o : nwtfr.c
	gcc -c $(OPT) nwtfr.c

# ======
# Neteja
# ======
clean :
	rm -f *.o
realclean : clean
	rm -f dibfr

