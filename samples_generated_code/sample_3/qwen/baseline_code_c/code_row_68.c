#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = {0};

    // Read the request line
    if (fgets(buffer, sizeof(buffer), request)) {
        // Extract the username assuming it's passed as a query parameter: /?username=example
        const char *query = strchr(buffer, '?');
        if (query) {
            const char *param = strstr(query, "username=");
            if (param) {
                param += strlen("username=");
                sscanf(param, "%255s", username);
            }
        }
    }

    // Construct the response
    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "Connection: close\r\n\r\n");
    fprintf(response, "hello %s\n", username);
}

int main() {
    // Example usage with stdin and stdout
    http_hello_page(stdin, stdout);
    return 0;
}