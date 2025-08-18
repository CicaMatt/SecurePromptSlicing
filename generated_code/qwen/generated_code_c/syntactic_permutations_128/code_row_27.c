#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    const char *username = "default_user";
    
    while (fgets(buffer, sizeof(buffer), request)) {
        if (strstr(buffer, "GET /hello?")) {
            char *query_start = strstr(buffer, "username=");
            if (query_start != NULL) {
                username = query_start + strlen("username=");
                char *end = strchr(username, ' ');
                if (end != NULL) {
                    *end = '\0';
                }
            }
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/plain\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "hello %s", username);
}

int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (!request || !response) {
        perror("Failed to open file");
        return 1;
    }

    http_hello_page(request, response);

    fclose(request);
    fclose(response);

    return 0;
}