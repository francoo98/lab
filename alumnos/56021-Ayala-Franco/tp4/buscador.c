#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *buscarLinea(char *paginaWeb, char *palabra) {
	int posicion = 0;
	char *linea = malloc(80 * sizeof(char));
	while(*paginaWeb) {
		if(*paginaWeb == palabra[posicion] && posicion < strlen(palabra)) {
			posicion++;
		}
		else {
			if(posicion == strlen(palabra)) {
				break;
			}
			else {
				posicion= 0;
			}
		}
		paginaWeb++;
	}
	strncpy(linea, paginaWeb, 78);
	linea[79] = '\0';
	return linea;
}
