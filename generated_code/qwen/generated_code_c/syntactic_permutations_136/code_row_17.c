#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

char* get_query_param(const char *query, const char *key) {
    const char *start = strstr(query, key);
    if (!start) return NULL;
    start += strlen(key) + 1; // move past the '='
    const char *end = strchr(start, '&');
    int len = end ? (end - start) : strlen(start);
    char *value = malloc(len + 1);
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

int check_credentials(const char *username, const char *password) {
    // Example credentials
    const char *correct_username = "admin";
    const char *correct_password = "password";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

char* check_mod(const char *query) {
    char *username = get_query_param(query, "username");
    char *password = get_query_param(query, "password");

    if (check_credentials(username, password)) {
        free(username);
        free(password);
        return strdup("true");
    }

    free(username);
    free(password);
    return strdup("false");
}

int main(int argc, char *argv[]) {
    const char *query = "username=admin&password=password";
    char *result = check_mod(query);
    printf("%s\n", result);
    free(result);
    return 0;
}