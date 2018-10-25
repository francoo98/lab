//GET /es/ua/fi.html HTTP/1.0
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"
#include "buscador.h"

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
	int socketDeCliente, leido, conectado, connSocketDeCliente, pid, i;
	char buff[1000] = "", bufferInternet[1000], url[220], palabra[22], dominio[22], archivo[100], *httpRequest, *linea = "";
	struct sockaddr_in procrem={};
	socketDeCliente = socket(AF_INET, SOCK_STREAM, 0);
	if  (socketDeCliente < 0 ){
		perror ("socket");
		return -1;
	}
	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(5000);
	//procrem.sin_addr = 192.168.1.52;
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	int a = 1;
	setsockopt(socketDeCliente, SOL_SOCKET, SO_REUSEADDR, &a, sizeof a);
	//inet_pton(AF_INET,"0.0.0.0", &procrem.sin_addr);
	if (bind(socketDeCliente,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
                return -1;
        }
	listen(socketDeCliente, 5);
	signal(SIGCHLD,SIG_IGN ); //para sacar procesos terminados de la PCB ...
	while ( (connSocketDeCliente = accept(socketDeCliente,NULL, 0)) > 0 ){
		pid = fork();
		//hijo
		if ( pid == 0 ) {
			leido = read (connSocketDeCliente,buff ,sizeof buff);  
			printf("%s\n", buff);
			separarUrlYPalabra(buff, url, palabra);
			printf("url: %s\npalabra: %s\n", url, palabra);
			separarDominioYArchivo(url, dominio, archivo);
			printf("%s\n", dominio);
			struct sockaddr_in socketInternet={};
			int fdSocketInternet = socket(AF_INET, SOCK_STREAM, 0);
			if(fdSocketInternet < 0) {
				perror("socket");
				return -1;
			}
			socketInternet.sin_family = AF_INET;
			socketInternet.sin_port = htons(80);
			struct hostent *hp = gethostbyname(dominio);
			inet_pton(AF_INET,inet_ntoa( *( struct in_addr*)( hp -> h_addr_list[0])), &socketInternet.sin_addr);
			conectado = connect(fdSocketInternet,(struct sockaddr *)&socketInternet, sizeof socketInternet);
			if(conectado < 0) {
				perror("connect");
				return -1;
			}
			httpRequest = armarHttpRequest(archivo);
			write(fdSocketInternet, httpRequest, strlen(httpRequest)); 
			//printf("strlen httprequest: %d\n", strlen(httpRequest));
			while((i = read(fdSocketInternet, bufferInternet, sizeof bufferInternet)) > 0) {
				linea = buscarLinea(bufferInternet, palabra);
				//printf("%s", bufferInternet);
				if(linea[0])	//se fija si linea tiene algo escrito. Si tiene algo, sale del while.
					break;		
			}
			i = write(connSocketDeCliente, linea, strlen(linea));
			//printf("i: %d\n", i); 
			//printf("linea: %s\n", linea);
			free(linea);
			free(httpRequest);
			return 0;
		}
		close(connSocketDeCliente);
	}
	return 0;
}
//setsocketopt() 
