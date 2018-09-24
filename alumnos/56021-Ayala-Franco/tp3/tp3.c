#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1000

int abrirArchivo(int argc, char ** argv);
extern void proc_contador();
extern void proc_mayus();

int main(int argc, char ** argv) {
	int fd = abrirArchivo(argc, argv);
	int leido;
	char *buffer = (char *)mmap(NULL, BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	sem_t *sem_contador = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 
	sem_t *sem_contadorPadre = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 
	sem_t *sem_mayus = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 
	sem_t *sem_mayusPadre = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 
	int *finDeArchivo= mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0); 
	pid_t pid_contador, pid_mayus;
	sem_init(sem_contador, 1, 0);
	sem_init(sem_contadorPadre, 1, 0);
	sem_init(sem_mayus, 1, 1);
	sem_init(sem_mayusPadre, 1, 0);
	if((pid_contador = fork()) == 0) {
		proc_contador(buffer, sem_contador, sem_contadorPadre, finDeArchivo);
		return 0;
	}
	if((pid_mayus = fork()) == 0) {
		proc_mayus(buffer, sem_mayus, sem_mayusPadre, finDeArchivo);
		return 0;
	}

	while((leido = read(fd, buffer, BUFFER_SIZE)) > 0) {
		sem_post(sem_contadorPadre);
		sem_post(sem_mayusPadre);	
		sem_wait(sem_contador);
		sem_wait(sem_mayus);
	}
	*finDeArchivo = 1;
	return 0;
}

int abrirArchivo(int argc, char ** argv) {
	getopt(argc, argv, "f:");
	int fd = open(optarg, O_RDONLY);
	if(fd == -1) {
		perror("open");
		_exit(EXIT_FAILURE);
	}      
	return fd;
}
