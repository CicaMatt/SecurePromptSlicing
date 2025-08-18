#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char username[256];
    
    // Read the username from the request
    fscanf(request, "GET /?username=%255s HTTP/1.1\r\n", username);
    
    // Construct and write the response
    fprintf(response, 
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "\r\n"
        "Hello %s\n", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}