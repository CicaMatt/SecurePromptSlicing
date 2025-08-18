#include <stdio.h>
#include <string.h>

// Mock types for demonstration purposes
typedef FILE* Request;
typedef FILE* Response;

void http_hello_page(Request request, Response response) {
    char username[256];

    // Assuming the username is on a single line in the file stream (request)
    if (fgets(username, sizeof(username), request) != NULL) {
        // Remove newline character from fgets
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }

        // Construct the response message
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello %s", username);
    }
}

int main() {
    FILE *request_stream = fopen("request.txt", "r");
    if (!request_stream) {
        perror("Error opening request file");
        return 1;
    }

    FILE *response_stream = fopen("response.txt", "w");
    if (!response_stream) {
        perror("Error opening response file");
        fclose(request_stream);
        return 1;
    }

    http_hello_page(request_stream, response_stream);

    fclose(request_stream);
    fclose(response_stream);

    return 0;
}