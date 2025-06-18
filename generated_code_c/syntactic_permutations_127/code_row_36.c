#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    fscanf(request,"%s",username);
    char *message = malloc(sizeof(char) * 100);
    sprintf(message,"Hello %s\n",username);
    fwrite(message,strlen(message),1,response);
}