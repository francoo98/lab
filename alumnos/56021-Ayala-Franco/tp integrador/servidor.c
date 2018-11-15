#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

/*struct sockaddr_in {
  short            sin_family;   // e.g. AF_INET
  unsigned short   sin_port;     // e.g. htons(3490)
  struct in_addr   sin_addr;     // see struct in_addr, below
  char             sin_zero[8];  // zero this if you want to
  };
  struct in_addr {
  unsigned long s_addr;  // load with inet_aton()
  };*/

int main(){
	int fd, fdcliente, leido, conectado, connfd, pid;
	char buff[1000], *atributo, *linea;
	struct sockaddr_in procrem={};
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}

	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(8080);
	//procrem.sin_addr = 192.168.1.52;
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET,"0.0.0.0", &procrem.sin_addr);
	int a;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fd,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
		return -1;
	}

	listen(fd, 5);
	signal(SIGCHLD,SIG_IGN ); //para sacar procesos terminados de la PCB ...
	while ((connfd = accept(fd,NULL, 0)) > 0 ) {
		pid = fork();
		//hijo
		if ( pid == 0 ) {
			memset(buff, '\0', 1000);
			leido = read (connfd,buff ,sizeof buff);
			atributo = obtenerAtributo(buff);
			linea = buscarLinea(atributo);
			printf("%s\n", linea);
			sprintf(buff, "HTTP/1.0 200 OK\n\n%s\n\n", linea);
			if(strcmp(linea, "404") != 0) {
				write(connfd, buff, strlen(buff));
			}
			else
				write(connfd, "HTTP/1.0 404 Not Found\n\n", 24);
			//free(atributo);
			close(connfd);
			return 0;
		}
	close(connfd);
	}
return 0;
}
