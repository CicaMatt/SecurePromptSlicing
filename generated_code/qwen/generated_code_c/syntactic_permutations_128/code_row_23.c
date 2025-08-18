#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char request_buffer[MAX_REQUEST_SIZE];
    char username[64] = "";
    
    if (fgets(request_buffer, sizeof(request_buffer), request) != NULL) {
        // Assuming the username is sent in plain text as part of the request
        sscanf(request_buffer, "%s", username);
        
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "hello %s\r\n", username);
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}