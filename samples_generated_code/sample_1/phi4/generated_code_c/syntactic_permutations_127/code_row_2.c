#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read username from request (assuming it's the first line and format "username=<value>")
    if (fgets(buffer, BUFFER_SIZE, request) != NULL) {
        char *pos = strstr(buffer, "username=");
        if (pos != NULL) {
            pos += 9; // Move past "username="
            char username[256];
            sscanf(pos, "%255[^&\n]", username); // Read until '&' or newline

            // Construct and write the response
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request");
        }
    } else {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nFailed to read request");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Simulated request file
    if (!request) return 1;

    FILE *response = fopen("response.txt", "w"); // Simulated response file
    if (!response) {
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}