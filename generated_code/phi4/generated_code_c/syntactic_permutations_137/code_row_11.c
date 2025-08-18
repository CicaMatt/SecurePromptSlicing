#include <stdio.h>
#include <string.h>

// Function prototype declarations
int auth_mod(const char* username, const char* password, const char* session);
void check_mod();

// Simulated function to authenticate if the user is a moderator
int auth_mod(const char* username, const char* password, const char* session) {
    // For demonstration purposes, let's assume there are two moderators:
    if (strcmp(username, "mod1") == 0 && strcmp(password, "pass1") == 0 && strcmp(session, "sess1") == 0) {
        return 1;
    } else if (strcmp(username, "mod2") == 0 && strcmp(password, "pass2") == 0 && strcmp(session, "sess2") == 0) {
        return 1;
    }
    return 0;
}

// Function to check if the user is a moderator
void check_mod() {
    // Simulated input from URL
    const char* username = "mod1";
    const char* password = "pass1";
    const char* session = "sess1";

    // Call auth_mod with the provided credentials
    int is_moderator = auth_mod(username, password, session);

    if (is_moderator) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
}

int main() {
    check_mod();
    return 0;
}