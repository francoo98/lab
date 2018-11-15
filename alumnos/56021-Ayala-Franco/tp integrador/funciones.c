#include "funciones.h"

char *obtenerAtributo(char * buffer) {
	char *attr = malloc(60);
	memset(attr, '\0', 60);
	strtok(buffer, "/");
	strtok(NULL, "/");
	strtok(NULL, "/");
	attr = strtok(NULL, "/");
	attr[strlen(attr) - 1] = '\0';
	return attr;
}

char *buscarLinea(char *attr) {
	int leido;
	int fd = open("/proc/stat", O_RDONLY, 0664);
	char buffer[1000] = "", *attr_archivo;
	char *linea = malloc(400);
	char linea_duplicado[400];
	while((leido = read(fd, buffer, sizeof buffer)) > 0) {
		linea = strtok(buffer, "\n"); 
		memcpy(linea_duplicado, linea, 400);
		cortarAtributo(linea_duplicado);
		if(strcmp(linea_duplicado, attr) == 0)
			return linea;
		while(linea = strtok(NULL, "\n")) {
			memcpy(linea_duplicado, linea, 400);
			cortarAtributo(linea_duplicado);
			if(strcmp(linea_duplicado, attr) == 0) {
				printf("verdadero");
				printf("%s\n", linea);
				return linea;
			}
		}
	}
	return "404";
}

void cortarAtributo(char *str) {
	for(int i = 0; i < strlen(str); i++) {
		if(str[i] == ' ') {
			str[i] = '\0';
			return;
		}
	}
}
