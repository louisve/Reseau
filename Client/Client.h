#include <stdio.h>
#include <stdlib.h> /* pour exit */
#include <unistd.h> /* pour close */
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h> /* pour memset */
#include <netinet/in.h> /* pour struct sockaddr_in */
#include <arpa/inet.h> /* pour htons et inet_aton */
#include <ctype.h>
#include <getopt.h>
#include <SDL2/SDL.h>
#include "../pixel.h"


#define LG_MESSAGE 256
#define TRUE 1



