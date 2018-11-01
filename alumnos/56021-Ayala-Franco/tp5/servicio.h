#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

struct serviceData {
	int connfd;
	char *configFile;
};

void servicio(struct serviceData *sd);
char *getResourcePath(char *buffer, char *rootDir);
void prepareResponseHeaders(char *, int, char *);
char *getContentType(char *resourcePath);
int getFileSize(int resourcefd);
void escribir404(int connfd);
