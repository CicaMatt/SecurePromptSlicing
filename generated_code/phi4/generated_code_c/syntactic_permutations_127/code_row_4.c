#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char buffer[BUFFER_SIZE];
    
    // Read request from client
    if (fgets(buffer, BUFFER_SIZE, request) != NULL) {
        char *username = NULL;
        
        // Extract username from the request assuming format: GET /hello?name=username HTTP/1.1
        if ((username = strstr(buffer, "name=")) != NULL) {
            username += 5; // Move past 'name='
            
            char end_of_username = '\0';
            for (int i = 0; i < strlen(username); ++i) {
                if (username[i] == '&') { // End of parameter or next parameter
                    end_of_username = username[i];
                    break;
                }
            }

            if (end_of_username != '\0') {
                username[end_of_username - 5] = '\0'; // Null-terminate the username
            } else {
                username[strlen(username)] = '\0'; // Ensure null termination
            }

            // Construct and write response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s", username);
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Invalid request format.");
        }
    } else {
        fprintf(response, "HTTP/1.1 500 Internal Server Error\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Failed to read the request.");
    }

    fflush(response);
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Simulating client request
    FILE *response = fopen("server_response.txt", "w"); // File to write response

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    } else {
        printf("Error opening files.\n");
    }

    return 0;
}