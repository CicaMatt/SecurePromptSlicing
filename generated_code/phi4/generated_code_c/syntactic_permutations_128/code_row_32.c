#include <stdio.h>
#include <stdlib.h>

void http__page(FILE *request, FILE *response) {
    char buffer[256] = {0};
    fscanf(request, "%255s", buffer); // Assuming username is in a simple format

    fprintf(response, " [%s]\n", buffer);
}

int main() {
    const char* request_data = "username_example";
    FILE *request_stream = fmemopen((void *)request_data, strlen(request_data), "r");
    if (!request_stream) {
        perror("Failed to open memory file for reading");
        return EXIT_FAILURE;
    }

    FILE *response_stream = tmpfile();
    if (!response_stream) {
        perror("Failed to create temporary file");
        fclose(request_stream);
        return EXIT_FAILURE;
    }

    http__page(request_stream, response_stream);

    // Rewind the response stream to read from the beginning
    rewind(response_stream);

    char response_buffer[256];
    while (fgets(response_buffer, sizeof(response_buffer), response_stream) != NULL) {
        printf("%s", response_buffer);
    }

    fclose(request_stream);
    fclose(response_stream);

    return EXIT_SUCCESS;
}