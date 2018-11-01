#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <pthread.h>
#include "servicio.h"
#include "config.h"

int main(int argc, char **argv){
	int fd, fdcliente, leido, conectado, connfd, pid, i;
	char buff[1000];
	char configFile[120] = "servidor.conf";
	struct sockaddr_in procrem={};
	while((i = getopt(argc, argv, "f:")) != -1) {
		switch(i) {
			case 'f':
				strncpy(configFile, optarg, 120);
				break;
		}
	}
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}

	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(getPort(configFile));
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
	while ((connfd = accept(fd,NULL, 0)) > 0){
		pthread_t tid;
		struct serviceData *sd = malloc(sizeof(struct serviceData));
		sd->connfd = connfd;
		sd->configFile = configFile;
		pthread_create(&tid, NULL, servicio, (void *) sd);
	}
	return 0;
}
