
tunalloc: iftun.o tunalloc.o extremite.o
	gcc -o tunalloc iftun.o tunalloc.o extremite.o

iftun.o: iftun.c
	gcc -o iftun.o -c iftun.c

extremite.o: extremite.c
	gcc -o extremite.o -c extremite.c

tunalloc.o: tunalloc.c iftun.h extremite.h
	gcc -o tunalloc.o -c tunalloc.c
