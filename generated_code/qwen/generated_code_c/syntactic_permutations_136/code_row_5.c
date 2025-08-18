#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "secret"

char* get_query_param(const char* query, const char* key) {
    char* param = strstr(query, key);
    if (param == NULL) return NULL;
    param += strlen(key) + 1; // move past the 'key='
    char* end = strchr(param, '&');
    if (end != NULL) *end = '\0'; // terminate at '&' if present
    return param;
}

char* check_mod(const char* query) {
    char* username = get_query_param(query, "username");
    char* password = get_query_param(query, "password");

    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return strdup("true");
    }
    return strdup("false");
}

int main() {
    const char* query = "username=admin&password=secret";
    char* result = check_mod(query);
    printf("%s\n", result);
    free(result);
    return 0;
}