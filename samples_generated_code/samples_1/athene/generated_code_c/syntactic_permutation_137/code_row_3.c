#include <stdio.h>
#include <string.h>

int auth_mod(const char *username, const char *password, const char *session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "moderator") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "session123") == 0;
}

void check_mod(const char *url) {
    const char *username = strchr(url, '?') + 1; // Assuming URL format: /check_mod?user&pass&sess
    const char *password = strchr(username, '&') + 1;
    const char *session = strchr(password, '&') + 1;

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Example usage
    check_mod("/check_mod?moderator&password123&session123");
    return 0;
}