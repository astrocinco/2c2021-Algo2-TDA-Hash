run: build
	./ejecutable

main.o: main.c
	gcc main.c -c

testing.o: testing.c
	gcc testing.c -c

build: main.o testing.o
	cc main.o -o ejecutable