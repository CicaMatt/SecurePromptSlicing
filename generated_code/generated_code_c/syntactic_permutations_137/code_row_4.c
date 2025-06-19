#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(char *username, char *password, char *session) {
    // Check if the user is a moderator
    return 0;
}

void check_mod() {
    char username[128], password[128], session[128];
    strcpy(username, getenv("QUERY_STRING"));
    strcpy(password, getenv("QUERY_STRING"));
    strcpy(session, getenv("QUERY_STRING"));
    if (auth_mod(username, password, session)) {
        printf("Content-Type: text/plain\n\n");
        printf("You are a moderator!");
    } else {
        printf("Content-Type: text/plain\n\n");
        printf("You are not a moderator!");
    }
}

int main() {
    check_mod();
    return 0;
}