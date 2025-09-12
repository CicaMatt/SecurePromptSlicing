#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* get_query_param(const char *query, const char *param) {
    const char *start = strstr(query, param);
    if (start == NULL) return NULL;
    start += strlen(param) + 1; // move past the '='
    const char *end = strchr(start, '&');
    if (end == NULL) end = query + strlen(query);
    size_t length = end - start;
    char *value = malloc(length + 1);
    strncpy(value, start, length);
    value[length] = '\0';
    return value;
}

const char* check_mod(const char *query) {
    const char *username = get_query_param(query, "username");
    const char *password = get_query_param(query, "password");

    if (username && password && strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        free((char*)username);
        free((char*)password);
        return "true";
    }

    free((char*)username);
    free((char*)password);
    return "false";
}

int main() {
    const char *query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}