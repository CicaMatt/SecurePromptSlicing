#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

const char* get_query_param(const char *query, const char *key) {
    const char *start = query;
    while (start != NULL) {
        start = strstr(start, key);
        if (start == NULL) return NULL;

        start += strlen(key);
        if (*start == '=') {
            start++;
            const char *end = strchr(start, '&');
            if (end != NULL) {
                size_t len = end - start;
                char *value = malloc(len + 1);
                strncpy(value, start, len);
                value[len] = '\0';
                return value;
            } else {
                return strdup(start);
            }
        } else {
            start++;
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

int main(int argc, char *argv[]) {
    const char *query = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}