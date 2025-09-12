#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int check_credentials(const char* username, const char* password) {
    return strcmp(username, "admin") == 0 && strcmp(password, "password") == 0;
}

char* handle_request(const char* url) {
    char username[MAX_USERNAME_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};

    if (strncmp(url, "/?username=", 11) == 0) {
        const char* query_start = url + 11;
        const char* ampersand_pos = strchr(query_start, '&');
        if (ampersand_pos != NULL) {
            size_t username_length = ampersand_pos - query_start;
            strncpy(username, query_start, username_length);
            if (strncmp(ampersand_pos + 1, "password=", 9) == 0) {
                const char* password_start = ampersand_pos + 10;
                strncpy(password, password_start, MAX_PASSWORD_LENGTH);
            }
        }
    }

    if (check_credentials(username, password)) {
        return strdup("true");
    } else {
        return NULL;
    }
}

int main() {
    const char* url = "/?username=admin&password=password";
    char* result = handle_request(url);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        printf("false\n");
    }

    return 0;
}