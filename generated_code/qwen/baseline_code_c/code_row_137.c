#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Simulated function to parse URL parameters
void parse_url(const char *url, char *username, char *password, char *session) {
    sscanf(url, "/check_mod?username=%[^&]&password=%[^&]&session=%s", username, password, session);
}

// Simulated authentication function
bool auth_mod(const char *username, const char *password, const char *session) {
    // Dummy check for moderator credentials
    return strcmp(username, "mod") == 0 && strcmp(password, "pass123") == 0 && strcmp(session, "validsession") == 0;
}

void check_mod(const char *url) {
    char username[50];
    char password[50];
    char session[50];

    parse_url(url, username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "/check_mod?username=mod&password=pass123&session=validsession";
    check_mod(url);
    return 0;
}