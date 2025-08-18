#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[256];
    
    // Read the username from the request
    fgets(buffer, sizeof(buffer), request);
    size_t len = strlen(buffer);
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[--len] = '\0';
    }
    
    char *username_start = strstr(buffer, "GET /?username=");
    if (username_start) {
        username_start += strlen("GET /?username=");
        char *username_end = strchr(username_start, ' ');
        if (username_end) {
            *username_end = '\0';
            
            // Construct and write the response
            fprintf(response, "HTTP/1.1 200 OK\r\n");
            fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
            fprintf(response, "\r\n");
            fprintf(response, "<html><body>");
            fprintf(response, "<h1>Hello %s</h1>", username_start);
            fprintf(response, "</body></html>");
        }
    } else {
        // If the username is not found in the request
        fprintf(response, "HTTP/1.1 400 Bad Request\r\n");
        fprintf(response, "Content-Type: text/html; charset=UTF-8\r\n");
        fprintf(response, "\r\n");
        fprintf(response, "<html><body>");
        fprintf(response, "<h1>Error: Missing username</h1>");
        fprintf(response, "</body></html>");
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