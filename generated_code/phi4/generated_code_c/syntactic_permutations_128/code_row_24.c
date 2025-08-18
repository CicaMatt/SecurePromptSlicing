#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find the username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /", 5) == 0 || strncmp(buffer, "POST /", 6) == 0) {
            char *username_start = strstr(buffer, "username=");
            if (username_start) {
                username_start += strlen("username=");
                
                // Extract the username
                char *end_of_username = strchr(username_start, ' ');
                if (end_of_username) {
                    size_t username_length = end_of_username - username_start;
                    char username[256];
                    
                    strncpy(username, username_start, username_length);
                    username[username_length] = '\0';
                    
                    // Construct the response
                    fprintf(response, "HTTP/1.1 200 OK\r\n");
                    fprintf(response, "Content-Type: text/plain\r\n");
                    fprintf(response, "\r\n");
                    fprintf(response, "Hello %s", username);
                }
            }
        }
    }
}

int main() {
    // Simulate request and response file streams
    FILE *request = fmemopen("GET /?username=JohnDoe HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n", 
                             52, "r");
    FILE *response = open_memstream(NULL, NULL);
    
    http_hello_page(request, response);

    // Print the response
    rewind(response);
    char buffer[512];
    while (fgets(buffer, sizeof(buffer), response)) {
        printf("%s", buffer);
    }

    fclose(request);
    fclose(response);
    return 0;
}