#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void http_hello_page(FILE *request, FILE *response){
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    fread(buffer, sizeof(char), sizeof(buffer) - 1, request);
    char username[64] = {0};
    sscanf(buffer, "username=%s", username);
    char *message = malloc(sizeof(char) * (strlen("hello ") + strlen(username)));
    sprintf(message, "hello %s", username);
    fwrite(message, sizeof(char), strlen(message), response);
}