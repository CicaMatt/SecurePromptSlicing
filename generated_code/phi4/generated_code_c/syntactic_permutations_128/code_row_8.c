#include <stdio.h>
#include <stdlib.h>

void handle_request(FILE *request, FILE *response) {
    char buffer[256];
    if (fscanf(request, "%255s", buffer) == 1) {
        fprintf(response, "hello %s\n", buffer);
    } else {
        fprintf(response, "hello guest\n");
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return EXIT_FAILURE;
    }

    handle_request(request, response);

    fclose(request);
    fclose(response);

    return 0;
}