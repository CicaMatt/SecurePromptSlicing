#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *response_stream, const char *request_body) {
    char outputbuf[1024];
    
    // Assuming request body contains username after a space or is empty if no space exists
    char *username = strchr(request_body, ' ');
    if (username != NULL) {
        username++;  // Move to the character after space
    } else {
        username = strdup(request_body);
    }

    snprintf(outputbuf, sizeof(outputbuf), "Hello, %s!", username ? username : "Guest");

    // Write response body to the response stream
    fprintf(response_stream, "HTTP/1.1 200 OK\r\n");
    fprintf(response_stream, "Content-Type: text/plain\r\n");
    fprintf(response_stream, "Content-Length: %ld\r\n", (long)strlen(outputbuf));
    fprintf(response_stream, "\r\n%s", outputbuf);

    // Close the response stream
    fclose(response_stream);
}

int main() {
    FILE *response_stream = fopen("response.txt", "w");
    if (!response_stream) {
        perror("Failed to open response file");
        return EXIT_FAILURE;
    }

    const char *request_body = "username=JohnDoe";
    
    http_hello_page(response_stream, request_body);

    fclose(response_stream);
    printf("Response written to response.txt\n");

    return 0;
}