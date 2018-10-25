#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *separarLinea(char *str) {
	char *linea = malloc(80 * sizeof(char));
	int i = 0;
	while(str[i] != '\n' && str[i]) {
		linea[i] = str[i];
		i++;
	}
	return linea;
}
int encontrarMayorQue(const char *s) {
	while(s) {
		if(*s == '>')
			return 1;
		s++;
	}
	return 0;
}

char *quitarTagsHtml(char *s) {
	int copy = 1, i = 0;
	int j = 0;
	char *str = malloc(80 * sizeof(char));
	while(s[i]) {
		if(s[i] == '<') {
			if(encontrarMayorQue(s))
				copy = 0;
		}
		if(copy) {
			str[j++] = s[i];
		}
		if(s[i] == '>')
			copy = 1;
		i++;
	}
	str[i] = '\0';
	return str;
}

char *buscarLinea(char *paginaWeb, char *palabra) {
	int posicion = 0;
	char *str = malloc(80 * sizeof(char));
	char *linea, *lineaSinHtml;
	while(*paginaWeb) {
		if(*paginaWeb == palabra[posicion] && posicion < strlen(palabra)) {
			posicion++;
		}
		else {
			if(posicion == strlen(palabra)) {
				break;
			}
			else {
				posicion = 0;
			}
		}
		paginaWeb++;
	}
	strncpy(str, paginaWeb, 78);
	linea = separarLinea(str);
	//printf("%s\n", linea);
	free(str);
	lineaSinHtml = quitarTagsHtml(linea);
	//printf("linea sin html: %s\n", lineaSinHtml);
	//printf("%s\n", str);
	//linea = strtok(paginaWeb, "\n");
	//printf("paginaweb: %s\n", paginaWeb);
	//printf("linea: %s\n", linea);
	//lineaSinHtml = quitarTagsHtml(linea);
	//printf("%s\n", lineaSinHtml);
	/*printf("pagina web: %s\n", paginaWeb);
	str[79] = '\0';
	printf("str: %s\n", str);
	linea = strtok(str, "\n");
	printf("linea: %p", linea);
	free(str);
	lineaSinHtml = quitarTagsHtml(linea);
	printf("lineaSinHtml: %s\n", lineaSinHtml);*/
	return lineaSinHtml;
}

/*int main() {
	char *s = "Hola</div>";
	char *ss = quitarTagsHtml(s);
	printf("%s\n", ss);
	return 0;
}*/
