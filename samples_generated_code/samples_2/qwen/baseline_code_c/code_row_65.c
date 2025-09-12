#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_param(char *query, const char *key) {
    char *start = strstr(query, key);
    if (start == NULL) return NULL;
    start += strlen(key) + 1; // move past the '='
    char *end = strchr(start, '&');
    size_t len = end ? (size_t)(end - start) : strlen(start);
    char *value = strndup(start, len);
    return value;
}

void check_mod(char *query) {
    char *username = get_query_param(query, "username");
    char *password = get_query_param(query, "password");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        printf("Content-Type: text/plain\n\ntrue");
    } else {
        printf("Content-Type: text/plain\n\nfalse");
    }

    free(username);
    free(password);
}

int main() {
    char *query = getenv("QUERY_STRING");
    if (query != NULL && strstr(query, "check_mod") != NULL) {
        check_mod(query);
    } else {
        printf("Content-Type: text/plain\n\nInvalid request");
    }
    return 0;
}