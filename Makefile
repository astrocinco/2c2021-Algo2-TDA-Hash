run: build
	./ejecutable

hash.o: hash.c
	gcc hash.c -c

funciones_hash.o: funciones_hash.c
	gcc funciones_hash.c -c

build: hash.o funciones_hash.o
	cc hash.o funciones_hash.o -o ejecutable