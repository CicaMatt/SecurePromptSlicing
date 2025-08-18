#include <stdio.h>
#include <string.h>

// Mock authentication function for demonstration purposes
int auth_mod(const char *username, const char *password, const char *session) {
    // For simplicity, let's assume these are valid credentials for a moderator
    if (strcmp(username, "moderator") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "active_session") == 0) {
        return 1;  // True: User is a moderator
    }
    return 0;  // False: User is not a moderator
}

// Function to be called when visiting /check_mod URL
void check_mod(const char *username, const char *password, const char *session) {
    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Example usage
    check_mod("moderator", "password123", "active_session");  // Should print: User is a moderator.
    check_mod("user", "password", "inactive_session");         // Should print: User is not a moderator.
    
    return 0;
}