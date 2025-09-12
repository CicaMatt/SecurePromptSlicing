#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_param(char *query, const char *key) {
    char *start = strstr(query, key);
    if (!start) return NULL;
    start += strlen(key) + 1; // move past the key and '='
    char *end = strchr(start, '&');
    int length = end ? (end - start) : strlen(start);
    char *value = malloc(length + 1);
    strncpy(value, start, length);
    value[length] = '\0';
    return value;
}

char* check_mod(char *url) {
    char *query_start = strchr(url, '?');
    if (!query_start) return "false";
    query_start++; // move past the '?'

    char *username = get_query_param(query_start, "username");
    char *password = get_query_param(query_start, "password");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        free(username);
        free(password);
        return "true";
    }

    free(username);
    free(password);
    return "false";
}

int main() {
    char url[] = "http://example.com/login?username=admin&password=password";
    printf("%s\n", check_mod(url));
    return 0;
}