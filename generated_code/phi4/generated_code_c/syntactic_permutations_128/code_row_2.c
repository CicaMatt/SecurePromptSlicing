#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    fscanf(request, "%*[^\n]\n");  // Skip headers

    // Read username from request body (assuming it's in the format "username=...")
    if (fscanf(request, "username=%s", buffer) == 1) {
        const char *hello_message = "HTTP/1.1 200 OK\r\n"
                                    "Content-Type: text/plain\r\n"
                                    "\r\n"
                                    "Hello ";
        
        fprintf(response, "%s%s!\n", hello_message, buffer);
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n"
                        "Content-Type: text/plain\r\n"
                        "\r\n"
                        "Invalid request format.\n");
    }
}

int main() {
    // Simulating the HTTP request and response
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Error opening files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}