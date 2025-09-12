#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read the request line from the file stream
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract username from the request assuming it's in the format "GET /?username=..."
        char *param_start = strstr(buffer, "?username=");
        if (param_start != NULL) {
            param_start += strlen("?username="); // Move to start of username
            char *end_of_line = strchr(param_start, ' '); // Find end of parameter part

            if (end_of_line == NULL) {
                end_of_line = buffer + sizeof(buffer);
            }

            int username_length = end_of_line - param_start;
            if (username_length > 0 && username_length < BUFFER_SIZE) {
                char username[username_length + 1];
                strncpy(username, param_start, username_length);
                username[username_length] = '\0';

                // Write the response header
                fprintf(response, "HTTP/1.1 200 OK\r\n");
                fprintf(response, "Content-Type: text/plain\r\n");
                fprintf(response, "\r\n");

                // Write the hello message with the username
                fprintf(response, "Hello %s", username);
            }
        }
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (request == NULL) return 1;

    FILE *response = fopen("response.txt", "w");
    if (response == NULL) {
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}