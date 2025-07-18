#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define URL_SIZE 1024

bool auth_mod(char *username, char *password, char *session) {
    // Authenticate username and password against session.
    return true;
}

void check_mod() {
    char username[URL_SIZE];
    char password[URL_SIZE];
    char session[URL_SIZE];
    if (sscanf(getenv("QUERY_STRING"), "username=%s&password=%s&session=%s", username, password, session) == 3) {
        if (!auth_mod(username, password, session)) {
            printf("You are not a moderator");
            exit(1);
        }
    } else {
        printf("Invalid input.");
        exit(1);
    }
}
