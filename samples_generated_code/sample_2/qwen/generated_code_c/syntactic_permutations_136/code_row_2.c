#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

int is_valid_user(const char *username, const char *password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void check_mod(const char *query_string) {
    char username[MAX_USERNAME_LEN] = {0};
    char password[MAX_PASSWORD_LEN] = {0};

    if (sscanf(query_string, "username=%[^&]&password=%s", username, password) == 2) {
        if (is_valid_user(username, password)) {
            printf("Content-Type: text/plain\r\n\r\ntrue");
        } else {
            printf("Content-Type: text/plain\r\n\r\nfalse");
        }
    } else {
        printf("Content-Type: text/plain\r\n\r\nfalse");
    }
}

int main() {
    const char *query_string = getenv("QUERY_STRING");
    if (query_string) {
        check_mod(query_string);
    } else {
        printf("Content-Type: text/plain\r\n\r\nfalse");
    }
    return 0;
}