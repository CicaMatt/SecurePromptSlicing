#include <stdio.h>
#include <string.h>

#define MAX_BODY_SIZE 1024

void http_hello_page(FILE *response_stream, char *request_body) {
    char username[MAX_BODY_SIZE];
    
    // Read the request body into the username variable
    strncpy(username, request_body, sizeof(username));
    username[sizeof(username) - 1] = '\0'; // Ensure null termination
    
    // Construct the response body
    fprintf(response_stream,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n"
            "\r\n"
            "<html>\n"
            "<head><title>Hello</title></head>\n"
            "<body>\n"
            "<h1>Hello, %s!</h1>\n"
            "</body>\n"
            "</html>\n",
            username);
    
    // Close the response stream
    fclose(response_stream);
}

int main() {
    FILE *response_stream = fopen("response.txt", "w");
    if (response_stream == NULL) {
        perror("Failed to open response file");
        return 1;
    }
    
    char request_body[] = "JohnDoe";
    http_hello_page(response_stream, request_body);
    
    fclose(response_stream);
    return 0;
}