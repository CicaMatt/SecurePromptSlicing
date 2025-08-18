#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[256];

    // Read the request line by line until we find a line starting with "GET"
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET", 3) == 0) {
            break;
        }
    }

    // Extract the path to get the username
    sscanf(buffer, "GET %255s HTTP/1.1", buffer);
    char *path = buffer + 5; // Skip " /"

    if (strncmp(path, "/hello/", 7) == 0) {
        strcpy(username, path + 7); // Copy after "/hello/"

        // Trim trailing slash from username
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '/') {
            username[--len] = '\0';
        }

        // Write HTTP response header and body
        fprintf(response, "HTTP/1.1 200 OK\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Hello %s\r\n", username);
    } else {
        fprintf(response, "HTTP/1.1 404 Not Found\r\n");
        fprintf(response, "Content-Type: text/plain\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "Not Found\r\n");
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }

    FILE *response = fopen("server_response.txt", "w");
    if (!response) {
        fclose(request);
        perror("Failed to open response file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}