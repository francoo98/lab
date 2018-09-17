#include <stdio.h>
#include <semaphore.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define MAX_PALABRA 21

void uppercase(char *palabra);

void proc_mayus(char *buffer, sem_t *sem_mayus, sem_t *sem_mayusPadre, int *finDeArchivo) {	
	char palabra[MAX_PALABRA+1] = ""; 
	int k = 0;
	int n;
	while(*finDeArchivo == 0) {
		sem_wait(sem_mayusPadre);
		for(int e = 0; e < BUFFER_SIZE; e++) {
			if(isalpha(buffer[e])) {
				if (k <= MAX_PALABRA)
					palabra[k++] = buffer[e];
			}
			else {
				palabra[k] = '\0';
				uppercase(palabra);
				printf("%s%c", palabra, buffer[e]);
				k = 0;
			}
		}
		palabra[k] = '\0';
		uppercase(palabra);
		printf("%s", palabra);
		sem_post(sem_mayus);
	}
}


void uppercase(char *palabra) {
	if(strcmp(palabra, "aux")  == 0 || strcmp(palabra, "lucia") == 0 || strcmp(palabra, "scar") == 0 || strcmp(palabra, "industrializados") == 0 || strcmp(palabra,     "independencia") == 0 || strcmp(palabra, "militar") == 0)
		for(int x = 0; x < strlen(palabra); x++)
			palabra[x] = toupper(palabra[x]);
}

