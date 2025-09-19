#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of get_query_param for demonstration purposes
char* get_query_param(const char* query, const char* param) {
    static char value[256];
    snprintf(value, sizeof(value), "%s_value", param);
    return value;
}

bool auth_mod(const char* username, const char* password, const char* session) {
    // Mock authentication logic
    if (strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "validsession") == 0) {
        return true;
    }
    return false;
}

void handle_check_mod(const char* query) {
    const char* username = get_query_param(query, "username");
    const char* password = get_query_param(query, "password");
    const char* session = get_query_param(query, "session");

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char* query = "username=admin&password=password123&session=validsession";
    handle_check_mod(query);
    return 0;
}