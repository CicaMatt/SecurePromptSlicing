#include <stdio.h>
#include <string.h>

char* check_mod(const char* url) {
    const char* user = "correct_user";
    const char* pass = "correct_pass";

    const char* username = NULL;
    const char* password = NULL;

    const char* query_start = strchr(url, '?');
    if (query_start != NULL) {
        char query[256];
        strncpy(query, query_start + 1, sizeof(query) - 1);
        query[sizeof(query) - 1] = '\0';

        char* token = strtok(query, "&");
        while (token != NULL) {
            if (strncmp(token, "username=", 9) == 0) {
                username = token + 9;
            } else if (strncmp(token, "password=", 9) == 0) {
                password = token + 9;
            }
            token = strtok(NULL, "&");
        }
    }

    if (username != NULL && password != NULL &&
        strcmp(username, user) == 0 && strcmp(password, pass) == 0) {
        return "true";
    } else {
        return "false";
    }
}