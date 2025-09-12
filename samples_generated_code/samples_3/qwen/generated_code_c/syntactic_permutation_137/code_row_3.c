#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of get_query_param for demonstration purposes
char* get_query_param(const char *url, const char *param) {
    static char value[256];
    sprintf(value, "%s_value", param);
    return value;
}

bool auth_mod(const char *username, const char *password, const char *session) {
    // Mock implementation of auth_mod for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session") == 0) {
        return true;
    }
    return false;
}

void check_mod(const char *url) {
    const char *username = get_query_param(url, "username");
    const char *password = get_query_param(url, "password");
    const char *session = get_query_param(url, "session");

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=secret&session=valid_session";
    check_mod(url);
    return 0;
}