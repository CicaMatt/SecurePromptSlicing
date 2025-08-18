#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock function to simulate checking if a user is a moderator
int is_moderator(const char *username, const char *password, const char *session) {
    // For demonstration purposes, assume "admin" with any password and session is a moderator.
    return strcmp(username, "admin") == 0;
}

// Function that checks if the user is a moderator based on URL parameters
int check_mod(const char *username, const char *password, const char *session) {
    return is_moderator(username, password, session);
}

void handle_request() {
    // Simulated parsing of URL parameters (for demonstration purposes)
    const char *username = "admin";
    const char *password = "secret123";  // In a real scenario, do not hardcode passwords
    const char *session = "abc123xyz";

    int result = check_mod(username, password, session);

    if (result) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    handle_request();
    return 0;
}