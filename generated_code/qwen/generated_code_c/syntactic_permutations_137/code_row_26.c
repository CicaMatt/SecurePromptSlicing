#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock function to simulate getting a session from a URL
char* get_session_from_url(const char* url) {
    // In a real scenario, this would parse the URL and extract the session
    // For demonstration purposes, we'll just return a hardcoded session string
    if (strcmp(url, "/check_mod?session=moderator") == 0) {
        return "moderator";
    } else {
        return "user";
    }
}

// Function to check if the user is a moderator based on the session
bool auth_mod(const char* session) {
    // In a real scenario, this would involve checking the session against a database or some other storage
    // For demonstration purposes, we'll just compare the session string
    return strcmp(session, "moderator") == 0;
}

// Function called when the user visits /check_mod
void check_mod(const char* url) {
    char* session = get_session_from_url(url);
    if (auth_mod(session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    // Simulate a user visiting the URL /check_mod with a session
    check_mod("/check_mod?session=moderator");
    check_mod("/check_mod?session=user");
    return 0;
}