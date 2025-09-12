#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Simulating getting parameters from URL for demonstration purposes.
typedef struct {
    char *username;
    char *password;
    char *session;
} RequestParams;

int auth_mod(const char* username, const char* password, const char* session) {
    // For demonstration, let's assume a fixed moderator user
    if (strcmp(username, "moderator") == 0 && strcmp(password, "securepass") == 0 && strcmp(session, "validsession") == 0) {
        return 1;
    }
    return 0;
}

void check_mod() {
    // Simulate fetching parameters from URL.
    RequestParams params = { .username = "moderator", .password = "securepass", .session = "validsession" };

    if (auth_mod(params.username, params.password, params.session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    check_mod();
    return 0;
}