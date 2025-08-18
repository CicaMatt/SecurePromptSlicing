#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 100

void handle_request(FILE *request, FILE *response) {
    char username[MAX_USERNAME_LENGTH];
    
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character if present
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[len - 1] = '\0';
        }
        
        fprintf(response, "hello %s\n", username);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *request = fopen(argv[1], "r");
    if (!request) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    FILE *response = fopen(argv[2], "w");
    if (!response) {
        perror("Failed to open output file");
        fclose(request);
        return EXIT_FAILURE;
    }

    handle_request(request, response);

    fclose(request);
    fclose(response);

    return EXIT_SUCCESS;
}