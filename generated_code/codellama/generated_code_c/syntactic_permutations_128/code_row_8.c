#include <stdio.h>

    void handle_request(FILE *request, FILE *response) {
        char username[256];
        fscanf(request, "%255s", username);
        fprintf(response, "hello %s\n", username);
    }