#include <stdio.h>
#include <string.h>

void http_hello_page(FILE *request, FILE *response) {
    char buffer[1024];
    char username[256] = "";
    int i, state = 0;

    while (fgets(buffer, sizeof(buffer), request)) {
        for (i = 0; buffer[i]; ++i) {
            if (state == 0 && buffer[i] == '?') {
                state = 1;
            } else if (state == 1 && (buffer[i] >= 'a' && buffer[i] <= 'z' || buffer[i] >= 'A' && buffer[i] <= 'Z')) {
                strcpy(username, &buffer[i]);
                while (username[strlen(username) - 1] != '=')
                    username[strlen(username) - 1] = '\0';
                state = 2;
            } else if (state == 2 && buffer[i] == '&') {
                username[strlen(username) - 1] = '\0';
                break;
            }
        }
    }

    fprintf(response, "HTTP/1.1 200 OK\r\n");
    fprintf(response, "Content-Type: text/html\r\n");
    fprintf(response, "\r\n");
    fprintf(response, "<html><body>Hello %s</body></html>", username);
}