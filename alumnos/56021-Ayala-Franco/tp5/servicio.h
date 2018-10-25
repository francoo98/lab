#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

char *getResourcePath(char *buffer);
void escribir404(int connfd);
void prepareResponseHeaders(char *, char *, char *);
void servicio(int connfd);
int getFileSize(int resourcefd);
char *getContentType(char *resourcePath);
char *getResourcePath(char *bufferClient);
