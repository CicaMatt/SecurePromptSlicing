#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the request line by line until we find a "GET" or "POST"
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strncmp(buffer, "GET", 3) == 0 || strncmp(buffer, "POST", 4) == 0) {
            break;
        }
    }

    // Extract the username from the request
    char *username = NULL;
    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");

    if (strcmp(method, "GET") == 0 || strcmp(method, "POST") == 0) {
        char *query_start = strchr(path, '?');
        if (query_start) {
            query_start++; // Move past the '?'
            username = strdup(query_start);
            char *end_of_username = strstr(username, " ");
            if (end_of_username) {
                *end_of_username = '\0'; // Null-terminate at space
            }
        }
    }

    if (!username || strlen(username) == 0) {
        fprintf(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\n");
        fprintf(response, "Bad request: No username provided.\r\n");
    } else {
        // Construct the response
        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        fprintf(response, "<html><body>");
        fprintf(response, "<h1>Hello %s</h1>", username);
        fprintf(response, "</body></html>\r\n");
    }

    free(username); // Free the allocated memory for username
}

int main() {
    FILE *request = fopen("client_request.txt", "r"); // Simulated client request file
    if (!request) {
        perror("Failed to open request file");
        return 1;
    }
    
    FILE *response = fopen("server_response.txt", "w"); // File for server response
    if (!response) {
        perror("Failed to open response file");
        fclose(request);
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}