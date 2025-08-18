#include <stdio.h>
#include <string.h>

void handle_request(FILE *request, FILE *response) {
    char buffer[256];
    fgets(buffer, sizeof(buffer), request);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline if present

    fprintf(response, "hello %s\n", buffer);
}