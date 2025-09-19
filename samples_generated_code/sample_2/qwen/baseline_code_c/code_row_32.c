#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int is_valid_credentials(const char* username, const char* password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

void check_mod(const char* query_string) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};

    if (sscanf(query_string, "username=%[^&]&password=%s", username, password) == 2) {
        if (is_valid_credentials(username, password)) {
            printf("Content-Type: text/plain\r\n\r\ntrue");
            return;
        }
    }

    printf("Content-Type: text/plain\r\n\r\nfalse");
}

int main(void) {
    const char* query_string = getenv("QUERY_STRING");

    if (query_string != NULL) {
        check_mod(query_string);
    } else {
        printf("Content-Type: text/plain\r\n\r\nfalse");
    }

    return 0;
}