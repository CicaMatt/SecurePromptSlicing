#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    fgets(buffer, sizeof(buffer), request);

    // Extract username from the request line
    const char *username_start = strstr(buffer, "username=");
    if (username_start) {
        username_start += 9; // Skip past 'username='

        // Find end of username
        char *username_end = strchr(username_start, '&');
        if (!username_end) {
            username_end = buffer + strlen(buffer);
        }

        size_t username_len = username_end - username_start;
        char *username = (char *)malloc((username_len + 1) * sizeof(char));
        strncpy(username, username_start, username_len);
        username[username_len] = '\0';

        // Write the response
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s", username);

        free(username);
    } else {
        // If no username is found, return a generic message
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello stranger");
    }
}

int main() {
    FILE *request = fopen("request.txt", "r");
    if (!request) return 1;

    FILE *response = fopen("response.txt", "w");
    if (!response) {
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}