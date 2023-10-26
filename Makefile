CC=       	gcc
CFLAGS= 	-g -gdwarf-2 -std=gnu99 -Wall -lmemalloc -pedantic -ansi --std=c99
CLFLAGS= 	-g -gdwarf-2 -std=gnu99 -Wall -pedantic -ansi
LDFLAGS=
LIBRARIES=      lib/libmemalloc.a

all:   unit_test benchmark1 benchmark2 benchmark3 benchmark4 benchmark5

benchmark1: benchmark1.o libmemalloc.a
	gcc -o benchmark1 benchmark1.o -L. -lmemalloc -g

benchmark2: benchmark2.o libmemalloc.a
	gcc -o benchmark2 benchmark2.o -L. -lmemalloc -g

benchmark3: benchmark3.o libmemalloc.a
	gcc -o benchmark3 benchmark3.o -L. -lmemalloc -g

benchmark4: benchmark4.o libmemalloc.a
	gcc -o benchmark4 benchmark4.o -L. -lmemalloc -g

benchmark5: benchmark5.o libmemalloc.a
	gcc -o benchmark5 benchmark5.o -L. -lmemalloc -g

unit_test: main.o libmemalloc.a
	gcc -o unit_test main.o -L. -lmemalloc -g

main.o: main.c
	gcc  -c  -Wall -Wno-self-assign -Wno-nonnull main.c -g 

benchmark1.o: benchmark1.c
	gcc  -c -Wall benchmark1.c -g

benchmark2.o: benchmark2.c
	gcc  -c -Wall benchmark2.c -g

benchmark3.o: benchmark3.c
	gcc  -c -Wall benchmark3.c -g

benchmark4.o: benchmark4.c
	gcc  -c -Wall benchmark4.c -g

benchmark5.o: benchmark5.c
	gcc  -c -Wall benchmark5.c -g

memalloc.o: memalloc.c
	gcc  -c  -Wall memalloc.c -g

libmemalloc.a: memalloc.o
	ar rcs libmemalloc.a memalloc.o

clean:
	rm -f *.o *.a unit_test main benchmark1 benchmark2 benchmark3 benchmark4 benchmark5

.PHONY: all clean
