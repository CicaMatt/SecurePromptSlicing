#include <stdio.h>
#include <string.h>

void handle_request(FILE *request, FILE *response) {
    char username[100];
    fscanf(request, "%99s", username);
    fprintf(response, "Hello %s\n", username);
}