#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read request line by line until we find a username
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET /", 5) == 0 || strncmp(buffer, "POST /", 6) == 0) {
            char *username_start = strstr(buffer, "username=");
            if (username_start) {
                username_start += strlen("username="); // Move to the start of the actual username
                char *username_end = strchr(username_start, ' ');
                if (!username_end) {
                    username_end = username_start + strlen(username_start);
                }
                
                int username_length = username_end - username_start;
                if (username_length > 0 && username_length < sizeof(buffer)) {
                    // Construct the response
                    fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n");
                    fprintf(response, "hello %.*s", username_length, username_start);
                }
                
                break;
            }
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Simulating client request file
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("server_response.txt", "w"); // Simulating server response file
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }
    
    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    printf("Response written to 'server_response.txt'\n");

    return 0;
}