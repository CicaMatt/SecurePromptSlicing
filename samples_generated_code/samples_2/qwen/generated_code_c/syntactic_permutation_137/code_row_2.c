#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void handle_request(const char* url) {
    if (strcmp(url, "/") == 0) {
        const char* username = "admin"; // Extracted from URL for demonstration
        const char* password = "password123"; // Extracted from URL for demonstration
        const char* session = "session123"; // Extracted from URL for demonstration

        bool is_moderator = auth_mod(username, password, session);
        if (is_moderator) {
            printf("User is a moderator.\n");
        } else {
            printf("User is not a moderator.\n");
        }
    }
}

int main() {
    handle_request("/");
    return 0;
}