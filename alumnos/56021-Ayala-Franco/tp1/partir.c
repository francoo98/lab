#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int tamano_ar(int);

int main(int argc, char **argv){
	int leido, size, i, fdi, fdo, flag, file_size, cArchivos;
	int outflag = 0;
	char out[20], outd[20];
	while((i = getopt(argc, argv, "i:o:s:n:h")) != -1)
	{
		switch(i)
		{
			case 'i':
				fdi = open(optarg, O_RDONLY);
				break;
			case 'o':
				strncpy(out, optarg, 20);
				strncpy(outd, optarg, 20);
				outflag = 1;
				break;
			case 's':
				size = atoi(optarg); 
				flag = 1;
				break;
			case 'n':
				cArchivos = atoi(optarg); 
				flag = 2;
				break;
			case 'h':
				printf("Opciones disponibles:\n -i archivo de entrada \n -o archivo de salida \n -s tamaño deseado de las partes (en bytes) \n -n numero de partes\n");
		}
	}
	if(flag == 1)
	{
		i = 1;
		char bufferr[size];
		while((leido = read(fdi, bufferr, size)) > 0)
		{
			if(outflag = 1)
			{
			snprintf(out, 20, "%s-part%d", outd, i);
			fdo = open(out, O_RDWR|O_CREAT, 0644);
			write(fdo, bufferr, leido);
			close(fdo);
			i++;
			}
			else
			{
			write(1, bufferr, leido);
			}
		}
	}
	else if(flag == 2)
	{
		file_size = tamano_ar(fdi);
		size = file_size/cArchivos;
		char buferr[size];
		for(i = 1; i <= cArchivos; i++)	
		{
			snprintf(out, 20, "%s-part%d", outd, i);
			fdo = open(out, O_RDWR|O_CREAT, 0644);
			if(i == cArchivos)
			{
				leido = read(fdi, buferr, file_size);
				write(fdo, buferr, leido);
			}
			else{
				leido = read(fdi, buferr, size);
				file_size = file_size - leido;
				write(fdo, buferr, leido);
			}	
				close(fdo);
		}
	}
	return 0;
}

int tamano_ar(int fd){
	char buffer[50];
	int tamano = 0;
	int leido;
	while((leido = read(fd, buffer, 50)) > 0)
	{
		tamano = tamano + leido;
	}
	lseek(fd, 0, SEEK_SET);
	return tamano;
}
