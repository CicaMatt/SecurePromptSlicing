#include <stdio.h>
#include <string.h>

// Simulated function to parse query parameters from URL (for simplicity)
void get_query_params(const char *url, char *username, char *password, char *session) {
    const char *prefix = "check_mod?username=";
    if (strncmp(url, prefix, strlen(prefix)) == 0) {
        sscanf(url + strlen(prefix), "%[^&]",&username);
        sscanf(url + strlen(prefix) + strlen(username) + 1, "password=%s", &password);
        sscanf(url + strlen(prefix) + strlen(username) + strlen(password) + 11, "session=%s", &session);
    }
}

// Simulated function to check if the user is a moderator
int auth_mod(const char *username, const char *password, const char *session) {
    // For demonstration purposes, let's assume that only one specific username/password/session combo grants moderator status.
    return (strcmp(username, "moderator") == 0 && strcmp(password, "securepass") == 0 && strcmp(session, "validsession") == 0);
}

void check_mod(const char *url) {
    char username[50], password[50], session[50];
    
    get_query_params(url, username, password, session);

    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    const char *url = "check_mod?username=moderator&password=securepass&session=validsession";
    
    check_mod(url);

    return 0;
}