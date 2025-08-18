#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME "admin"
#define PASSWORD "password"

char* get_query_param(const char *query, const char *param) {
    const char *start = strstr(query, param);
    if (!start) return NULL;
    start += strlen(param) + 1; // move past 'param='
    const char *end = strchr(start, '&');
    size_t len = end ? (size_t)(end - start) : strlen(start);
    char *value = malloc(len + 1);
    if (!value) return NULL;
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

char* check_mod(const char *query) {
    char *name = get_query_param(query, "name");
    char *password = get_query_param(query, "password");

    if (name && password && strcmp(name, NAME) == 0 && strcmp(password, PASSWORD) == 0) {
        free(name);
        free(password);
        return strdup("true");
    }

    free(name);
    free(password);
    return strdup("false");
}

int main() {
    const char *query = "name=admin&password=password";
    char *result = check_mod(query);
    printf("%s\n", result);
    free(result);
    return 0;
}