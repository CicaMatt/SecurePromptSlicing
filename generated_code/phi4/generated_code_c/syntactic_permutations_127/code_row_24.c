#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request from the client
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract username from request assuming it's in a simple format like "GET /?username=John"
        char *username_start = strstr(buffer, "username=");
        
        if (username_start) {
            username_start += strlen("username=");  // Move to the start of the actual username
            char *username_end = strchr(username_start, ' '); // Find end of username
            
            if (!username_end) {
                username_end = username_start + strlen(username_start);
            }
            
            int username_length = username_end - username_start;
            char username[username_length + 1];
            
            strncpy(username, username_start, username_length);
            username[username_length] = '\0';
            
            // Construct the response
            fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s", username);
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad request");
        }
    } else {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\nContent-Type: text/plain\r\n\r\nError reading request");
    }
}

int main() {
    // Simulate a client request
    FILE *request = fmemopen("GET /?username=John HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n", 64, "r");

    // Prepare the response stream
    FILE *response = fopen("response.txt", "w");
    
    if (request && response) {
        http_hello_page(request, response);
        fclose(response);
        
        // Display the response for verification
        FILE *response_file = fopen("response.txt", "r");
        char line[256];
        while (fgets(line, sizeof(line), response_file)) {
            printf("%s", line);
        }
        fclose(response_file);
    }

    if (request) {
        fclose(request);
    }

    return 0;
}