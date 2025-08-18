#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[100];
    memset(buffer, 0, sizeof(buffer));
    memset(username, 0, sizeof(username));

    while (fgets(buffer, sizeof(buffer), request)) {
        if (sscanf(buffer, "username=%s", username) == 1) {
            break;
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}
int main() {
    FILE *request = fopen("request.txt", "r");
    FILE *response = fopen("response.txt", "w");

    if (request && response) {
        http_hello_page(request, response);

        fclose(request);
        fclose(response);
    }
    return 0;
}