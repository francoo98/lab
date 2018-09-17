#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int tamano(int);
int main(int argc, char **argv){	
	char buff[50] = "";
	char nombre_archivo[25] = "";
	int fdo, fdi, i, size;
	int bytes = 0;
	int fin = 1;
	void * memoria;
	int outflag = 0;
	while((i = getopt(argc, argv, "o:h")) != -1)
	{
		switch (i)
		{
			case 'h':
				printf("Ingresar partes a unir usando ls *-part* y pipe. La opcion -o especifica el nombre del archivo donde escribir");
				break;
			case 'o':
				outflag = 1;
				fdo = open(optarg, O_CREAT|O_APPEND|O_RDWR,0644);
				break; 
		}
	}
	i = 1;
	while(fin != 0)
	{
		if(bytes != 0)
		{
			fin = read(0, nombre_archivo, bytes);
			nombre_archivo[bytes-1] = '\0';
			//buff[bytes-1] = '\0';
			//strcat(nombre_archivo, buff);
			i++;
			if(i == 9)
				bytes++;
		} else {
			do
			{
				strcat(nombre_archivo, buff);
				bytes++;
				fin = read(0, buff, 1);
			} while(buff[0] != '\n');
		}	
		memset(buff, '\0', 50);
		fdi = open(nombre_archivo, O_RDONLY);
		size = tamano(fdi);
		memoria = malloc(size);
		read(fdi, memoria, size);
		if(outflag == 1)
			write(fdo, memoria, size);
		else
			write(1, memoria, size);
		close(fdi);
		free(memoria);
		memset(nombre_archivo, '\0', 25);
		memset(buff, '\0', 50);
	}
	close(fdo);	
	return 0;
}

int tamano(int fdi)
{
	char buffer[50];
	int tamano = 0;
	int leido;
	while((leido = read(fdi, buffer, 50)) > 0)
	{
		tamano = tamano + leido;
	}
	lseek(fdi, 0, SEEK_SET);
	return tamano;
}
