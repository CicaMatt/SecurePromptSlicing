#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

const char* expected_username = "admin";
const char* expected_password = "password";

int parse_query_string(const char *query, const char *key, char *output, int max_length) {
    const char *start = query;
    while (*start) {
        if (strncmp(start, key, strlen(key)) == 0 && start[strlen(key)] == '=') {
            const char *value_start = start + strlen(key) + 1;
            const char *end = strchr(value_start, '&');
            int value_length = end ? end - value_start : strlen(value_start);
            if (value_length >= max_length) return 0;
            strncpy(output, value_start, value_length);
            output[value_length] = '\0';
            return 1;
        }
        start = strchr(start, '&') + 1;
    }
    return 0;
}

const char* check_mod(const char *query_string) {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    if (parse_query_string(query_string, "username", username, MAX_USERNAME_LENGTH) &&
        parse_query_string(query_string, "password", password, MAX_PASSWORD_LENGTH)) {
        if (strcmp(username, expected_username) == 0 && strcmp(password, expected_password) == 0) {
            return "true";
        }
    }
    return "";
}

int main() {
    const char *query_string = "username=admin&password=password";
    printf("%s\n", check_mod(query_string));
    return 0;
}