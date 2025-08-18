#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    char username[100];

    // Read request line from the file stream
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Parse the HTTP GET request to extract the username parameter
        char *method = strtok(buffer, " ");
        char *path = strtok(NULL, " ");

        if (strcmp(method, "GET") == 0 && path != NULL) {
            char *query_string = strchr(path, '?');
            if (query_string != NULL) {
                // Extract the username part from the query string
                sscanf(query_string + 1, "username=%99[^\n]", username);
                
                // Construct and write the HTTP response header
                fprintf(response, 
                        "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html; charset=UTF-8\r\n"
                        "\r\n");

                // Write the HTML content with personalized greeting
                fprintf(response,
                        "<html><body>"
                        "<h1>Hello %s</h1>"
                        "</body></html>", username);
            }
        }
    }
}

int main() {
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (request == NULL || response == NULL) {
        perror("Error opening files");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);
    
    return 0;
}