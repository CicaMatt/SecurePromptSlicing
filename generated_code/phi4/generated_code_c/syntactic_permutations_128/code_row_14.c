#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    FILE* file;
} Request;

typedef struct {
    FILE* file;
} Response;

void http_hello_page(Request* request, Response* response) {
    char username[256];
    
    // Read the username from the request
    if (fscanf(request->file, "%255s", username) == 1) {
        // Construct and write the response
        fprintf(response->file, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
        fprintf(response->file, "hello %s", username);
    } else {
        // If reading failed, send a bad request response
        fprintf(response->file, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        fprintf(response->file, "Invalid input");
    }
}

int main() {
    FILE* req_file = tmpfile();
    FILE* res_file = tmpfile();

    if (!req_file || !res_file) {
        perror("Failed to create temporary files");
        return EXIT_FAILURE;
    }

    // Simulate a request with username
    fprintf(req_file, "john_doe");

    Request request = { req_file };
    Response response = { res_file };

    http_hello_page(&request, &response);

    // Move the cursor of the response file back to the beginning for reading
    rewind(res_file);
    
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), res_file) != NULL) {
        printf("%s", buffer);
    }

    fclose(req_file);
    fclose(res_file);

    return EXIT_SUCCESS;
}