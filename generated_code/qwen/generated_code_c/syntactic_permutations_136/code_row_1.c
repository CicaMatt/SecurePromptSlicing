#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* query) {
    const char* username = NULL;
    const char* password = NULL;
    char* result = (char*)malloc(5 * sizeof(char));

    if (query != NULL) {
        char* query_copy = strdup(query);
        char* token = strtok(query_copy, "&");
        while (token != NULL) {
            if (strncmp(token, "username=", 9) == 0) {
                username = token + 9;
            } else if (strncmp(token, "password=", 9) == 0) {
                password = token + 9;
            }
            token = strtok(NULL, "&");
        }
        free(query_copy);
    }

    if (username != NULL && password != NULL) {
        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            strcpy(result, "true");
            return result;
        }
    }
    strcpy(result, "false");
    return result;
}

int main() {
    const char* query = "username=admin&password=password";
    char* response = check_mod(query);
    printf("%s\n", response);
    free(response);
    return 0;
}