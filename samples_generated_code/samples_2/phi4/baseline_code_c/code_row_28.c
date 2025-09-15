#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read request from the file stream (simulated as a single line input)
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract username from the request
        char *username_start = strstr(buffer, "username=");
        if (username_start) {
            username_start += 9; // Move to the start of the username
            char *username_end = strchr(username_start, ' ');
            if (username_end) {
                size_t username_length = username_end - username_start;
                char *username = strndup(username_start, username_length);
                
                // Construct and write response
                fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello %s\n", username);
                
                free(username); // Free the allocated memory for username
            }
        }
    }

    // Send a basic HTTP response header if no username is found or malformed request
    fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request format.\n");
}

int main() {
    FILE *request = fopen("request.txt", "r"); // Simulated client request file
    FILE *response = fopen("response.txt", "w"); // File to write the response

    if (request && response) {
        http_hello_page(request, response);
        fclose(request);
        fclose(response);

        // Read and print response for demonstration purposes
        char line[256];
        FILE *response_read = fopen("response.txt", "r");
        while (fgets(line, sizeof(line), response_read)) {
            printf("%s", line);
        }
        fclose(response_read);
    } else {
        perror("File opening failed");
    }

    return 0;
}
