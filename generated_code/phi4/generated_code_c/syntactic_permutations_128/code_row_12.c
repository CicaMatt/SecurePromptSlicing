#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    fseek(request, 0, SEEK_SET); // Reset file pointer to start of request

    // Read first line of HTTP request which is usually in the format "GET /path?username=value"
    if (fgets(buffer, sizeof(buffer), request) == NULL) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Error reading the request.\n");
    } else {
        char *username = strstr(buffer, "username=");
        
        if (username) {
            username += 9; // Move pointer to start of actual username
            char *end_of_username = strchr(username, '&');
            size_t username_length;

            if (end_of_username) {
                username_length = end_of_username - username;
            } else {
                username_length = strlen(username);
            }

            char user_name_copy[256];
            strncpy(user_name_copy, username, username_length);
            user_name_copy[username_length] = '\0';

            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Hello %s\n", user_name_copy);
        } else {
            fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
            fprintf(response, "Content-Type: text/plain\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "Username not provided.\n");
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Error opening request file");
        return 1;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        perror("Error opening response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}