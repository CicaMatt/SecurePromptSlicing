#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_value(char *query, const char *key) {
    char *value = NULL;
    char *p = strstr(query, key);
    if (p != NULL) {
        p += strlen(key) + 1; // move pointer to the start of value
        char *end = strchr(p, '&');
        if (end != NULL) {
            *end = '\0'; // null-terminate the value
        }
        value = strdup(p);
    }
    return value;
}

char* check_mod(char *query) {
    char *username = get_query_value(query, "username");
    char *password = get_query_value(query, "password");

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
    char url[] = "http://example.com?username=admin&password=password";
    char *query = strchr(url, '?') + 1;
    char *result = check_mod(query);
    printf("%s\n", result);
    free(result);
    return 0;
}