#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char *username, const char *password) {
    // This function would normally query a database.
    // For demonstration purposes, we'll use hardcoded values.
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void handle_login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        printf("Content-type: text/html\r\n");
        printf("Location: home.html\r\n\r\n");
    } else {
        printf("Content-type: text/html\r\n");
        printf("Location: login.html\r\n\r\n");
    }
}

int main() {
    char *method = getenv("REQUEST_METHOD");

    if (method == NULL || strcmp(method, "POST") != 0) {
        printf("Content-type: text/plain\r\n\r\nInvalid request method.");
        return 1;
    }

    char username[MAX_USERNAME_LENGTH + 1] = {0};
    char password[MAX_PASSWORD_LENGTH + 1] = {0};

    int content_length = atoi(getenv("CONTENT_LENGTH"));

    if (content_length <= 0) {
        printf("Content-type: text/plain\r\n\r\nNo data received.");
        return 1;
    }

    char *data = malloc(content_length + 1);
    if (data == NULL) {
        printf("Content-type: text/plain\r\n\r\nMemory allocation failed.");
        return 1;
    }

    fread(data, content_length, 1, stdin);
    data[content_length] = '\0';

    sscanf(data, "username=%[^&]&password=%s", username, password);

    free(data);

    handle_login(username, password);

    return 0;
}