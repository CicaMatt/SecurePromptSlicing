#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from the request
    if (fgets(buffer, sizeof(buffer), request) != NULL) {
        // Extract the username assuming it's after a space in a GET request line
        char *username = strtok(buffer, " ");
        if (username != NULL) {
            username = strtok(NULL, " ");  // Move to the next token (the path)
            if (username != NULL && strcmp(username, "/") == 0) {
                // Assuming the username is passed as a query parameter like ?username=John
                char *query_str = strtok(NULL, "\r\n");
                if (query_str != NULL) {
                    char *eq_pos = strstr(query_str, "username=");
                    if (eq_pos != NULL) {
                        eq_pos += strlen("username=");  // Move to the start of username value
                        char *end_pos = strchr(eq_pos, ' ');
                        size_t len = end_pos ? (size_t)(end_pos - eq_pos) : strlen(eq_pos);
                        
                        // Write the response header
                        fprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n");
                        
                        // Construct and write the response body
                        char response_body[256];
                        snprintf(response_body, sizeof(response_body), "Hello %.*s", (int)len, eq_pos);
                        fprintf(response, "%s\r\n", response_body);
                    }
                }
            }
        }
    }
}

int main() {
    // Example usage
    FILE *request = fopen("client_request.txt", "r");
    FILE *response = fopen("server_response.txt", "w");

    if (request != NULL && response != NULL) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    }

    return 0;
}