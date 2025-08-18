#include <stdio.h>
#include <string.h>

void http_hello_page(const char *request, char *response) {
    const char *prefix = "GET /?username=";
    const size_t prefix_len = strlen(prefix);
    if (strncmp(request, prefix, prefix_len) == 0) {
        const char *username = request + prefix_len;
        char *end_of_username = strchr(username, ' ');
        if (end_of_username) {
            *end_of_username = '\0';
        }
        snprintf(response, 1024, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello %s", username);
    } else {
        snprintf(response, 1024, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request");
    }
}

int main() {
    char request[1024] = "GET /?username=JohnDoe HTTP/1.1";
    char response[1024];
    http_hello_page(request, response);
    printf("%s", response);
    return 0;
}