main : main.o pixel.o
	gcc -o main main.o pixel.o -lm -g

main.o: main.c
	gcc -g -Wall -c main.c

pixel.o: pixel.c
	gcc -g -Wall -c pixel.c

clean:
	rm *.o