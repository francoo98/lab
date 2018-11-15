/*

No se pueden abrir archivos pdf

*/
#include "servicio.h"

void servicio(struct serviceData *sd) {
	char bufferClient[1000], bufferResource[50000], *resourcePath, responseHeaders[200], *aux;
	int resourcefd, fileSize;
	int bytesRead = read(sd->connfd, bufferClient, sizeof bufferClient);
	resourcePath = getResourcePath(bufferClient, getRootDir(sd->configFile));
	resourcefd = open(resourcePath, O_RDONLY);
	if(resourcefd < 0) {
		escribir404(sd->connfd);
		pthread_exit(NULL);
	}
	prepareResponseHeaders(responseHeaders, resourcefd, resourcePath);
	write(sd->connfd, responseHeaders, strlen(responseHeaders));
	while((bytesRead = read(resourcefd, bufferResource, 50000)) > 0) {
		write(sd->connfd, bufferResource, bytesRead);
		//write(1, bufferResource, bytesRead);
	}
	write(sd->connfd, "\n\n", 2);
	close(sd->connfd);
	pthread_exit(NULL);
}

char *getResourcePath(char *bufferClient, char *rootDir) {
	char *resourcePath = malloc(120 * sizeof(char));
	char *resource;
	int i = 0;
	strtok(bufferClient, " ");
	resource = strtok(NULL, " ");
	strcpy(resourcePath, rootDir);
	strcat(resourcePath, resource);
	printf("%s\n", resourcePath);
	return resourcePath;	
}

void prepareResponseHeaders(char *responseHeaders, int resourcefd, char *resourcePath) {
	int fileSize = getFileSize(resourcefd);
	char *contentType = getContentType(resourcePath);
	printf("content-type: %s\n", contentType);
	snprintf(responseHeaders, 200, "HTTP/1.0 200 OK\nContent-Length: %d\nContent-Type: %s\n\n", fileSize, contentType);
	printf("responseHeaders: %s\n", responseHeaders);
	free(contentType);
}

char *getContentType(char *resourcePath) {
	char *contentType = malloc(32 * sizeof(char));
	strtok(resourcePath, ".");
	char *s = strtok(NULL, ".");
	if(strcmp(s, "pdf") == 0) {
		snprintf(contentType, 32, "application/pdf");
		return contentType;
	}
	if(strcmp(s, "txt") == 0) {
		snprintf(contentType, 22, "text/plain");
		return contentType;
	}
	if(strcmp(s, "html") == 0) { 
		snprintf(contentType, 22, "text/html");
		return contentType;
	}
	if(strcmp(s, "png") == 0 || strcmp(s, "jpg") == 0) {
		snprintf(contentType, 22, "image/%s", s);
		return contentType;
	}
}

int getFileSize(int resourcefd) {
	struct stat data;
	fstat(resourcefd, &data);
	return data.st_size;
}

void escribir404(int connfd) {
	write(connfd, "HTTP/1.0 404 Not Found\nContent-Length: 26\nContent-Type: text/html\n\n<h1>404 Not Found :'(</h1>\n\n", 101);
}
