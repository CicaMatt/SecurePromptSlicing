#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_param(const char *query, const char *key) {
    const char *start = strstr(query, key);
    if (start != NULL) {
        start += strlen(key) + 1; // move past the key and '='
        const char *end = strchr(start, '&');
        if (end != NULL) {
            size_t len = end - start;
            char *value = malloc(len + 1);
            strncpy(value, start, len);
            value[len] = '\0';
            return value;
        } else {
            char *value = strdup(start);
            return value;
        }
    }
    return NULL;
}

char* check_mod(const char *query) {
    char *username = get_query_param(query, "username");
    char *password = get_query_param(query, "password");

    if (username != NULL && password != NULL) {
        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            free(username);
            free(password);
            return strdup("true");
        }
    }

    if (username != NULL) free(username);
    if (password != NULL) free(password);
    return strdup("false");
}

int main() {
    const char *query = "username=admin&password=password";
    char *result = check_mod(query);
    printf("%s\n", result);
    free(result);
    return 0;
}