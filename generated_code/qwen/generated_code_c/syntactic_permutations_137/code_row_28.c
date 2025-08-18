#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy authentication logic for demonstration purposes
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0 && strcmp(session, "validsession") == 0;
}

void check_mod(const char* url) {
    // Extracting username, password, and session from the URL
    const char* query = strchr(url, '?') + 1;
    char username[50], password[50], session[50];
    sscanf(query, "username=%49[^&]&password=%49[^&]&session=%49s", username, password, session);

    // Authenticating the user
    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char* url = "http://example.com/check_mod?username=admin&password=password123&session=validsession";
    check_mod(url);
    return 0;
}