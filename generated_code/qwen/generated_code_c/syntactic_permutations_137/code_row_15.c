#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50
#define MAX_SESSION_LEN 100

int auth_mod(const char* username, const char* password, const char* session) {
    // Dummy implementation for demonstration purposes
    if (strcmp(username, "admin") == 0 && strcmp(password, "adminpass") == 0 && strcmp(session, "validsession") == 0) {
        return 1; // true
    }
    return 0; // false
}

void check_mod(const char* username, const char* password, const char* session) {
    if (auth_mod(username, password, session)) {
        printf("User is a moderator.\n");
    } else {
        printf("User is not a moderator.\n");
    }
}

int main() {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char session[MAX_SESSION_LEN];

    // Simulating user input for demonstration purposes
    strcpy(username, "admin");
    strcpy(password, "adminpass");
    strcpy(session, "validsession");

    check_mod(username, password, session);

    return 0;
}