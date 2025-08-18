#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* get_query_param(const char *query, const char *key) {
    const char *start = strstr(query, key);
    if (start == NULL) return NULL;
    start += strlen(key) + 1; // Move past the '=' character
    const char *end = strchr(start, '&');
    int length = end ? end - start : strlen(start);
    char *value = malloc(length + 1);
    strncpy(value, start, length);
    value[length] = '\0';
    return value;
}

const char* check_mod(const char *query) {
    const char *username = get_query_param(query, "username");
    const char *password = get_query_param(query, "password");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        free((void*)username);
        free((void*)password);
        return "true";
    }

    free((void*)username);
    free((void*)password);
    return "false";
}

int main() {
    const char *query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}