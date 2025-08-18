#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_param(char *query, const char *key) {
    char *start = strstr(query, key);
    if (!start) return NULL;
    start += strlen(key) + 1; // move past the '='
    char *end = strchr(start, '&');
    if (end) *end = '\0'; // terminate at '&' if present
    return start;
}

char* check_mod(char *url) {
    char query[256];
    sscanf(url, "http://example.com/?%s", query);

    char *username = get_query_param(query, "username");
    char *password = get_query_param(query, "password");

    if (username && password && strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return strdup("true");
    }
    return NULL;
}

int main() {
    char url[] = "http://example.com/?username=admin&password=password";
    char *result = check_mod(url);
    if (result) {
        printf("%s\n", result);
        free(result); // free the duplicated string
    } else {
        printf("false\n");
    }
    return 0;
}