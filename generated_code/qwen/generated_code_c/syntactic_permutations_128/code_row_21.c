#include <stdio.h>
#include <string.h>

void http_hello_page(const char* request, char* response) {
    const char* username_start = strstr(request, "username=");
    if (username_start != NULL) {
        username_start += 9; // Move past "username="
        char username[100];
        int i = 0;
        while (username_start[i] != ' ' && username_start[i] != '\n' && username_start[i] != '&' && i < sizeof(username) - 1) {
            username[i] = username_start[i];
            i++;
        }
        username[i] = '\0';
        snprintf(response, 256, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello %s", username);
    } else {
        strcpy(response, "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nInvalid request");
    }
}

int main() {
    char request[] = "GET /?username=Alice HTTP/1.1";
    char response[256];
    http_hello_page(request, response);
    printf("%s", response);
    return 0;
}