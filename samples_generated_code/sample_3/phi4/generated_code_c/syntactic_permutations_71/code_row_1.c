#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1048576 // Maximum file size of 1MB

void print_usage() {
    printf("Usage: ./file_upload_server <port>\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_usage();
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        printf("Invalid port number. Please provide a valid port between 1 and 65535.\n");
        return EXIT_FAILURE;
    }

    char buffer[MAX_FILE_SIZE];
    FILE *uploaded_file;

    printf("Simple File Upload Server started on port %d\n", port);

    while (1) {
        printf("Waiting for file upload...\n");

        // Simulate receiving data from a client
        printf("Enter filename to save: ");
        char filename[256];
        scanf("%s", filename);
        
        uploaded_file = fopen(filename, "wb");
        if (!uploaded_file) {
            perror("Error opening file");
            continue;
        }

        int bytes_received = 0;
        while (bytes_received < MAX_FILE_SIZE) {
            printf("Enter data to write (%d/%d): ", bytes_received, MAX_FILE_SIZE);
            char input[256];
            scanf("%255s", input);

            if (strlen(input) == 0) break;

            int input_length = strlen(input);
            fwrite(input, sizeof(char), input_length, uploaded_file);
            bytes_received += input_length;
        }

        fclose(uploaded_file);
        
        printf("File upload complete.\n");
    }

    return EXIT_SUCCESS;
}