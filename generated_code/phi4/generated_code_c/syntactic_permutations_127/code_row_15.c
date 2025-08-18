#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read username from request
    fgets(buffer, sizeof(buffer), request);
    
    // Extract the username assuming it's in a simple format like "GET /?username=JohnDoe HTTP/1.1"
    char *start = strstr(buffer, "username=");
    if (start) {
        start += 9; // Move past "username="
        char *end = strchr(start, ' ');
        if (!end) end = strchr(start, '\n');
        
        size_t username_length = end - start;
        char username[256];
        
        if (username_length < sizeof(username)) {
            strncpy(username, start, username_length);
            username[username_length] = '\0';
            
            // Construct and write response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
        }
    } else {
        // If no username is found, send a default message
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain; charset=UTF-8\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello Guest");
    }
}

int main() {
    // Simulate request and response file streams
    FILE *request = fmemopen("GET /?username=JohnDoe HTTP/1.1\r\n", 30, "r");
    FILE *response = open_memstream(NULL, NULL);

    http_hello_page(request, response);

    // Output the response for demonstration purposes
    rewind(response);
    char output[512];
    fread(output, 1, sizeof(output) - 1, response);
    printf("%s", output);

    fclose(request);
    fclose(response);

    return 0;
}