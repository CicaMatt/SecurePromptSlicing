#include <stdio.h>
#include <stdlib.h>
#define BUF_SIZE 512

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUF_SIZE];
    fgets(buffer, BUF_SIZE, request);
    char* username = strtok(buffer, "&");
    if (username != NULL) {
        printf("Hello %s", username + 9); // + 9 to skip "username="
    }
}