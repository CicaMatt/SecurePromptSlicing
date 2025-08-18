#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of get_query_param to simulate extracting parameters from URL
char* get_query_param(const char* query, const char* param) {
    static char value[1024];
    snprintf(value, sizeof(value), "%s_value", param);
    return value;
}

bool auth_mod(const char* username, const char* password, const char* session) {
    // Mock implementation of auth_mod function
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session") == 0;
}

void check_mod(const char* query) {
    char* username = get_query_param(query, "username");
    char* password = get_query_param(query, "password");
    char* session = get_query_param(query, "session");

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char* query = "username=admin&password=secret&session=valid_session";
    check_mod(query);
    return 0;
}