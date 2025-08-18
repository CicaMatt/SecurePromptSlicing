#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* get_query_param(char *query, const char *param) {
    char *p = query;
    while (p != NULL && *p != '\0') {
        if (strncmp(p, param, strlen(param)) == 0 && p[strlen(param)] == '=') {
            return p + strlen(param) + 1;
        }
        p = strchr(p, '&');
        if (p != NULL) {
            p++;
        }
    }
    return NULL;
}

char* check_mod(char *query) {
    char *username = get_query_param(query, "username");
    char *password = get_query_param(query, "password");

    if (username && password) {
        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            return "true";
        }
    }
    return "false";
}

int main() {
    char query[] = "username=admin&password=password";
    printf("%s\n", check_mod(query));
    return 0;
}