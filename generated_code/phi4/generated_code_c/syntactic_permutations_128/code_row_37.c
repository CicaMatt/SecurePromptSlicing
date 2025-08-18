#include <stdio.h>
#include <stdlib.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line from the file stream (assuming the username is on the first line)
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Find the start of the username in the buffer
        const char *username_start = "username=";
        size_t len = strlen(username_start);
        
        if (strncmp(buffer, "GET /?", 6) == 0) { // Simple check for query format
            char *query = buffer + 6;
            char *username_pos = strstr(query, username_start);
            
            if (username_pos) {
                username_pos += len; // Move past 'username=' to get the actual name
                
                // Extract username till end or space/newline
                const char *username_end = strchr(username_pos, '&');
                if (!username_end) {
                    username_end = strchr(username_pos, '\n');
                }
                
                size_t username_length = username_end ? (size_t)(username_end - username_pos) : strlen(username_pos);
                
                // Write the response header
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");
                
                // Construct and write the hello message with username
                char response_message[512];
                snprintf(response_message, sizeof(response_message), "hello %.*s", (int)username_length, username_pos);
                fputs(response_message, response);
            }
        }
    } else {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fputs("Bad request format", response);
    }
}

int main() {
    // Example usage
    FILE *request = fopen("client_request.txt", "r"); // This should be the path to your client's request file.
    if (!request) {
        perror("Failed to open request file");
        return EXIT_FAILURE;
    }

    FILE *response = tmpfile(); // Create a temporary file for response
    if (!response) {
        perror("Failed to create response file");
        fclose(request);
        return EXIT_FAILURE;
    }
    
    http_hello_page(request, response);

    // Rewind and print the response content
    rewind(response);
    char ch;
    while ((ch = fgetc(response)) != EOF) {
        putchar(ch);
    }

    fclose(request);
    fclose(response);

    return 0;
}