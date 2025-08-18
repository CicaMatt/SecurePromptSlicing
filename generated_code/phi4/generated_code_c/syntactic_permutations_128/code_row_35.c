#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[256];

    // Read request line (assuming simple GET method with no headers)
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract the path from the request line
        sscanf(buffer, "GET %255s HTTP/1.1", buffer);

        // Assuming the URL is in format "/hello?username=[username]"
        char *query = strchr(buffer, '?');
        if (query && strstr(query, "username=")) {
            strcpy(username, query + strlen("username="));
            char *end = strchr(username, ' ');
            if (end) {
                *end = '\0';
            }
        }
    }

    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
    fprintf(response, "\r\n");

    if (strlen(username) > 0) {
        fprintf(response, "Hello %s", username);
    } else {
        fprintf(response, "Hello guest");
    }
}

int main() {
    // Example usage
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);
        fclose(request);
        fclose(response);
    }

    return 0;
}