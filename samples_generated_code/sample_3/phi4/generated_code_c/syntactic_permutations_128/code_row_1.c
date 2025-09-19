#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char request_line[256];
    
    // Read the first line from the request which contains the GET method and username
    if (fgets(request_line, sizeof(request_line), request) != NULL) {
        // Extract the username part after "GET /?username="
        const char *start = strstr(request_line, "GET /?username=");

        if (start) {
            start += strlen("GET /?username=");
            
            // Find where the username ends
            char *end = strchr(start, ' ');
            if (end) {
                size_t username_length = end - start;
                char username[256];
                
                // Copy only the username part into a buffer
                strncpy(username, start, username_length);
                username[username_length] = '\0';

                // Construct and write response
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                fprintf(response, "Hello %s", username);
            }
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Simulated request file
    FILE *response = fopen("server_response.txt", "w"); // Simulated response file

    if (request && response) {
        http_hello_page(request, response);
        
        fclose(request);
        fclose(response);
    }

    return 0;
}