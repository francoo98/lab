#ifndef _PALABRAS_H_
#define _PALABRAS_H_

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/types.h>
	#include <ctype.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <errno.h>
	#include <sys/wait.h>
	
		void obtenerPalabras(char **palabras);
		int obtenerCantidadPalabras(char *palabras);
  
#endif
