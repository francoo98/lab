/* Codigo de hijo que cuenta la cantidad de palabras */
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUFFER_SIZE 1000
#define MAX_PALABRA 21

void proc_contador(char *buf , sem_t *sem_contador, sem_t *sem_contadorPadre, int *finDeArchivo) {
	int palabras[MAX_PALABRA] = {0};
	int letras = 0;
	while(*finDeArchivo == 0) {
		sem_wait(sem_contadorPadre);
		for(int e = 0; e < BUFFER_SIZE; e++) {
			if(isalpha(*(buf + e*sizeof(char))))
				letras++;
			else {
				if(letras <= MAX_PALABRA) 
					palabras[letras - 1]++;
				letras = 0;
			}
		}
		sem_post(sem_contador);
	}
	for(int e = 0; e < MAX_PALABRA; e++) {
		if(palabras[e] != 0) {
			printf("Palabras de %d letras: %d\n", e+1, palabras[e]);
		}
	}
}
