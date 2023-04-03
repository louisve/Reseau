serveur : serveur.o pixel.o
	gcc -o serveur --static serveur.o pixel.o -lm -g

serveur.o: serveur.c
	gcc -g -Wall -c serveur.c

pixel.o: pixel.c
	gcc -g -Wall -c pixel.c

clean:
	rm *.o
