#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_param(const char *query, const char *key) {
    const char *start = strstr(query, key);
    if (!start) return NULL;
    start += strlen(key) + 1; // move past the '='
    const char *end = strchr(start, '&');
    if (!end) end = start + strlen(start); // if no '&' then it's at the end of string
    size_t len = end - start;
    char *value = malloc(len + 1);
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

char* check_mod(const char *query) {
    char *username = get_query_param(query, "username");
    char *password = get_query_param(query, "password");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
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