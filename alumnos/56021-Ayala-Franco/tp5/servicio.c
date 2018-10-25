#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char *getContentType(char *resourcePath) {
	char *contentType = malloc(22 * sizeof(char));
	strtok(resourcePath, ".");
	char *s = strtok(NULL, ".");
	if(strcmp(s, "html") == 0 || strcmp(s, "txt") == 0)
		snprintf(contentType, 22, "text/%s", s);
	else {
		if(strcmp(s, "png") == 0 || strcmp(s, "jpg") == 0)
			snprintf(contentType, 22, "image/%s", s);
	}
	return contentType;
}

int getFileSize(int resourcefd) {
	struct stat data;
	fstat(resourcefd, &data);
	return data.st_size;
}

void prepareResponseHeaders(char *responseHeaders, int resourcefd, char *resourcePath) {
	int fileSize = getFileSize(resourcefd);
	char *contentType = getContentType(resourcePath);
	printf("content-type: %s\n", contentType);
	snprintf(responseHeaders, 200, "HTTP/1.0 200 OK\nContent-Length: %d\nContent-Type: %s\n\n", fileSize, contentType);
}

void escribir404(int connfd) {
	write(connfd, "HTTP/1.0 404 Not Found\nContent-Length: 26\nContent-Type: text/html\n\n<h1>404 Not Found :'(</h1>\n\n", 101);
}

char *getResourcePath(char *bufferClient) {
	char *resourcePath;
	int i = 0;
	strtok(bufferClient, " ");
	resourcePath = strtok(NULL, " ");
	for(i = 0; i < strlen(resourcePath)-1; i++) {
		resourcePath[i] = resourcePath[i+1];
	}
	resourcePath[i] = '\0';
	return resourcePath;	
}

void servicio(int connfd) {
	char bufferClient[1000], bufferResource[1000], *resourcePath, responseHeaders[200], *aux;
	int resourcefd, fileSize;
	int bytesRead = read(connfd, bufferClient, sizeof bufferClient);
	resourcePath = getResourcePath(bufferClient);
	resourcefd = open(resourcePath, O_RDONLY);
	if(resourcefd < 0) {
		escribir404(connfd);
		pthread_exit(NULL);
	}
	prepareResponseHeaders(responseHeaders, resourcefd, resourcePath);
	write(connfd, responseHeaders, strlen(responseHeaders));
	while((bytesRead = read(resourcefd, bufferResource, 1000)) > 0) {
		write(connfd, bufferResource, bytesRead);
	}
	write(connfd, "\n\n", 2);
	pthread_exit(NULL);
}
