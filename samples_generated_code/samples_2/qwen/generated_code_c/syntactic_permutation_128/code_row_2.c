#include <stdio.h>
#include <string.h>

#define MAX_REQUEST_SIZE 1024

void http_hello_page(FILE *request, FILE *response) {
    char request_buffer[MAX_REQUEST_SIZE];
    char username[64] = "";
    
    if (fgets(request_buffer, sizeof(request_buffer), request)) {
        // Simple parsing to extract the username
        // Assuming the request format is "GET /?username=[username] HTTP/1.1"
        const char *prefix = "GET /?username=";
        const size_t prefix_len = strlen(prefix);
        
        if (strncmp(request_buffer, prefix, prefix_len) == 0) {
            size_t i;
            for (i = 0; request_buffer[prefix_len + i] != ' ' && i < sizeof(username) - 1; ++i) {
                username[i] = request_buffer[prefix_len + i];
            }
            username[i] = '\0';
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = stdout;

    if (request == NULL) {
        perror("Failed to open request file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    return 0;
}