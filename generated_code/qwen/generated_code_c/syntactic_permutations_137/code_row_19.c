#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of parsing URL parameters
void parse_url(const char* url, char* username, char* password, char* session) {
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
}

// Mock implementation of authentication function
bool auth_mod(const char* username, const char* password, const char* session) {
    // Dummy check: return true for moderator if username is "admin"
    return strcmp(username, "admin") == 0;
}

void check_mod(const char* url) {
    char username[100];
    char password[100];
    char session[100];

    parse_url(url, username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char* test_url = "/check_mod?username=admin&password=secret&session=12345";
    check_mod(test_url);
    return 0;
}