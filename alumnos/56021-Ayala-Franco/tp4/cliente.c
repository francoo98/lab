#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
	char url[150] = "", palabra[22], mensaje[200] = "", buffer[1000];
	int puerto = 5000, socketfd, i, conectado;
	struct sockaddr_in procrem={};
	memset(buffer, 0, sizeof buffer);
	while((i = getopt(argc, argv, "u:t:p:h")) != -1) {
		switch(i) {
			case 'u':
				strncpy(url, optarg, 150);
				break;
			case 't':
				strncpy(palabra, optarg, 22);
				break;
			case 'p':
				puerto = atoi(optarg);
				break;
			case 'h':	
				printf("u: pagina web.\nt: palabra.\np: puerto.");
				return 0;
				break;
		}
	}	
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if(socketfd < 0) {
		perror("socket");
	}
	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(puerto);
	inet_pton(AF_INET, "127.0.0.1", &procrem.sin_addr);
	conectado = connect(socketfd,(struct sockaddr *)&procrem, sizeof procrem);
	if  (conectado < 0 )	{
                perror ("connect");
                return -1;
	}
	/*strncpy(mensaje, url, 115);
	strcat(mensaje, "{}");
	strcat(mensaje, palabra);*/
	//snprintf("%s{}%s", url, palabra);
	dprintf(socketfd, "%s{}%s", url, palabra);
	write(socketfd, mensaje, 115);
	//printf("mensaje: %s\n", mensaje);
	read(socketfd, buffer, 1000);
	printf("%s\n", buffer);
	return 0;
}
