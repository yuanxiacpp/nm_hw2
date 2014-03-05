all: project2

project2: project2.c
	gcc -g -o project2 project2.c -lm

clean:
	rm *~ project2
