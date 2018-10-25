#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int getPort() {
	int confFileFd = open("servidor.conf", O_RDONLY);
	int port;
	char buffer[1000], *line, *portstring;
	read(confFileFd, buffer, sizeof buffer);
	line = strtok(buffer, "\n");
	strtok(line, "=");
	portstring = strtok(NULL, "=");
	port = atoi(portstring);
	return port;
}

char *getRootDir() {
	int confFileFd = open("servidor.conf", O_RDONLY);
	char buffer[1000], *line = malloc(sizeof(char));
	read(confFileFd, buffer, sizeof buffer);
	strtok(buffer, "\n");
	line = strtok(NULL, "\n");
	line = strtok(line, "=");
	line = strtok(NULL, "=");
	return line;
}
