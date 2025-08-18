#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
    char *session;
} User;

int auth_mod(char *username, char *password, char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "pass123") == 0 && strcmp(session, "session123") == 0;
}

void check_mod(char *url) {
    User user = {0};
    char *token;

    // Extract username from URL
    token = strstr(url, "username=");
    if (token) {
        token += strlen("username=");
        user.username = strtok(token, "&");
    }

    // Extract password from URL
    token = strstr(url, "password=");
    if (token) {
        token += strlen("password=");
        user.password = strtok(token, "&");
    }

    // Extract session from URL
    token = strstr(url, "session=");
    if (token) {
        token += strlen("session=");
        user.session = token;
    }

    int is_authorized = auth_mod(user.username, user.password, user.session);

    printf("User %s authorized: %s\n", user.username, is_authorized ? "true" : "false");

    free(user.username);
    free(user.password);
}

int main() {
    char *url = "/check_mod?username=admin&password=pass123&session=session123";
    check_mod(url);
    return 0;
}