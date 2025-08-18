#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* get_query_param(const char *query, const char *key) {
    const char *start = query;
    while (start != NULL && *start != '\0') {
        start = strstr(start, key);
        if (start == NULL) break;

        start += strlen(key);
        if (*start == '=') {
            start++;
            const char *end = strchr(start, '&');
            int len = end ? end - start : strlen(start);
            char *result = malloc(len + 1);
            strncpy(result, start, len);
            result[len] = '\0';
            return result;
        }
    }
    return NULL;
}

const char* check_mod(const char *query) {
    const char *username = get_query_param(query, "username");
    const char *password = get_query_param(query, "password");

    if (username != NULL && password != NULL &&
        strcmp(username, USERNAME) == 0 &&
        strcmp(password, PASSWORD) == 0) {
        free((void*)username);
        free((void*)password);
        return "true";
    }

    if (username != NULL) free((void*)username);
    if (password != NULL) free((void*)password);

    return "false";
}

int main() {
    const char *query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}