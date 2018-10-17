#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funciones.h"

void separarUrlYPalabra(char *buffer, char *url, char *palabra) {
	int esUrl = 1;
	while(*buffer) {
		if(*buffer == '{' && *(buffer+1) == '}') {
			buffer += 2;
			esUrl = 0;
		}
		if(esUrl) {
			*url = *buffer;
			url++;
			buffer++;
		}
		else {
			*palabra = *buffer;
			palabra++;
			buffer++;
		}
	}
	*url = '\0';
	*palabra = '\0';
}

void separarDominioYArchivo(char *url, char *dominio, char *archivo) {
	int esDominio = 1, cantidadDeSlash = 0;
	while(*url) {
		if(*url == '/' && *(url-1) != '/' && *(url+1) != '/')
			esDominio = 0;
		if(esDominio) {
			if(cantidadDeSlash == 2) {
			*dominio = *url;
			dominio++;
			}
		}
		else {
			*archivo = *url;
			archivo++;
		}
		if(*url == '/' && cantidadDeSlash < 2)
			cantidadDeSlash++;
		url++;
	}
	*archivo = '\0';
	*dominio = '\0';
}

char *armarHttpRequest(char *archivo) {
	char *r_ptr = malloc(120 * sizeof(char));
	strcpy(r_ptr, "GET ");
	strcat(r_ptr, archivo);
	strcat(r_ptr, " HTTP/1.0\n\n");
	return r_ptr;
}
