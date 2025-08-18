#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0 && strcmp(session, "valid_session") == 0;
}

void handle_root_url(const char *url) {
    const char *username = "admin";
    const char *password = "secret";
    const char *session = "valid_session";

    // Extracting parameters from URL would typically involve parsing
    // For this example, they are hardcoded

    bool is_moderator = auth_mod(username, password, session);
    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/";
    handle_root_url(url);
    return 0;
}