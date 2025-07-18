#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int redirect_invalid_url(const char* url) {
    if (strcmp(url, ".") == 0 || strcmp(url, "..") == 0) {
        printf("Error: Invalid URL\n");
        return -1;
    }
    // Redirect the user to the URL.
    char* redirect_url = malloc(strlen(url) + 4);
    strcpy(redirect_url, "http://");
    strcat(redirect_url, url);
    printf("Redirecting to %s\n", redirect_url);
    free(redirect_url);
    return 0;
}