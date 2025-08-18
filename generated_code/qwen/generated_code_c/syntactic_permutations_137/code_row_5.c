#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock function to simulate authentication
bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy check for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "validsession") == 0;
}

// Function to handle the /check_mod URL request
void check_mod(const char* url) {
    // Parsing the URL for username, password, and session
    const char* query = strchr(url, '?') + 1;
    char username[50], password[50], session[50];
    sscanf(query, "username=%[^&]&password=%[^&]&session=%s", username, password, session);

    // Authenticating the user as a moderator
    bool is_moderator = auth_mod(username, password, session);

    if (is_moderator) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator.\n", username);
    }
}

int main() {
    // Simulate visiting the URL with specific parameters
    const char* url = "/check_mod?username=admin&password=password123&session=validsession";
    check_mod(url);
    return 0;
}