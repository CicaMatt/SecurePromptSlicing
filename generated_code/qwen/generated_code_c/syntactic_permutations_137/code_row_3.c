#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Mock implementation of URL parsing functions for demonstration purposes
void get_username(char *url, char *username) {
    sscanf(url, "/check_mod?username=%[^&]", username);
}

void get_password(char *url, char *password) {
    sscanf(url, "/check_mod?username=%*[^&]&password=%[^&]", password);
}

void get_session(char *url, char *session) {
    sscanf(url, "/check_mod?username=%*[^&]&password=%*[^&]&session=%s", session);
}

// Mock implementation of auth_mod function for demonstration purposes
bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy check: return true if username is "mod" and password is "secret"
    return strcmp(username, "mod") == 0 && strcmp(password, "secret") == 0;
}

void check_mod(char *url) {
    char username[100];
    char password[100];
    char session[100];

    get_username(url, username);
    get_password(url, password);
    get_session(url, session);

    bool is_moderator = auth_mod(username, password, session);

    if (is_moderator) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    char url[] = "/check_mod?username=mod&password=secret&session=12345";
    check_mod(url);
    return 0;
}