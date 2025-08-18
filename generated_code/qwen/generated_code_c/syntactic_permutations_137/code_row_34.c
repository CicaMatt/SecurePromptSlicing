#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0;
}

void check_mod(const char *url) {
    const char *prefix = "/check_mod?username=";
    const char *username_start = url + strlen(prefix);
    
    if (strncmp(url, prefix, strlen(prefix)) != 0) {
        printf("Invalid URL\n");
        return;
    }

    const char *password_start = strchr(username_start, '&') + 10; // Assuming "&password=" after username
    const char *session_start = strchr(password_start, '&') + 8;   // Assuming "&session=" after password

    if (!password_start || !session_start) {
        printf("Invalid URL parameters\n");
        return;
    }

    char username[50], password[50], session[50];
    strncpy(username, username_start, password_start - username_start - 1);
    strncpy(password, password_start, session_start - password_start - 1);
    strcpy(session, session_start);

    int is_moderator = auth_mod(username, password, session);
    if (is_moderator) {
        printf("User is a moderator\n");
    } else {
        printf("User is not a moderator\n");
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=secret&session=12345";
    check_mod(url);
    return 0;
}