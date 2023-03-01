main : main.o
	gcc -o main main.o -lm -g

main.o: main.c
	gcc -g -Wall -c main.c

clean:
	rm main* .o