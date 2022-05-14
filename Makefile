CFLAGS = -g -Wall -Wextra -pedantic 
CC = gcc

PROGRAMS = main mainH main_test calcul main_testH

.PHONY:	all clean

all: $(PROGRAMS)

main: main.o  entreeSortieLC.o biblioLC.o
	$(CC) -o $@ $(CFLAGS) $^

mainH: mainH.o  entreeSortieH.o biblioH.o
	$(CC) -o $@ $(CFLAGS) $^

main_test: main_test.o  entreeSortieLC.o biblioLC.o
	$(CC) -o $@ $(CFLAGS) $^

main_testH: main_testH.o  entreeSortieH.o biblioH.o
	$(CC) -o $@ $(CFLAGS) $^

calcul: calcul.o  entreeSortieLC.o entreeSortieH.o biblioLC.o biblioH.o
	$(CC) -o $@ $(CFLAGS) $^

entreeSortieLC.o: entreeSortieLC.c
	$(CC) -c $(CFLAGS) entreeSortieLC.c 

biblioLC.o: biblioLC.c
	$(CC) -c $(CFLAGS) biblioLC.c

entreeSortieH.o: entreeSortieH.c
	$(CC) -c $(CFLAGS) entreeSortieH.c 

biblioH.o: biblioH.c
	$(CC) -c $(CFLAGS) biblioH.c

clean:
	rm -f *.o *~ $(PROGRAMS)
