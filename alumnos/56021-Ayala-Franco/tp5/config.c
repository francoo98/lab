#include "config.h"

int getPort(char *configFile) {
	int confFileFd = open(configFile, O_RDONLY);
	int port;
	char buffer[1000], *line, *portstring;
	read(confFileFd, buffer, sizeof buffer);
	line = strtok(buffer, "\n");
	strtok(line, "=");
	portstring = strtok(NULL, "=");
	port = atoi(portstring);
	return port;
}

char *getRootDir(char *configFile) {
	int confFileFd = open(configFile, O_RDONLY);
	char buffer[1000], *line = malloc(sizeof(char));
	read(confFileFd, buffer, sizeof buffer);
	strtok(buffer, "\n");
	line = strtok(NULL, "\n");
	line = strtok(line, "=");
	line = strtok(NULL, "=");
	return line;
}
