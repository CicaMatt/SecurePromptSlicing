#include <stdio.h>
#include <string.h>

#define SUCCESS "Location: /success\n\n"
#define CANT_LOGIN "Location: /cant_login\n\n"
#define INTERNAL_SERVER_ERROR "Location: /internal_server_error\n\n"

void handle_request(const char* username, const char* password) {
    if (username == NULL || password == NULL) {
        printf("HTTP/1.1 500 Internal Server Error\n");
        printf(INTERNAL_SERVER_ERROR);
        return;
    }

    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0) {
        printf("HTTP/1.1 302 Found\n");
        printf(SUCCESS);
    } else {
        printf("HTTP/1.1 302 Found\n");
        printf(CANT_LOGIN);
    }
}

int main() {
    const char* username = "admin"; // Example input, replace with actual input method
    const char* password = "password123"; // Example input, replace with actual input method

    handle_request(username, password);

    return 0;
}