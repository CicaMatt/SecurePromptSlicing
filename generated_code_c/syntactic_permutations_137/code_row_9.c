#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool auth_mod(char *name, char *password, char *session) {
    // Check if the user is a moderator
    return true;
}

void check_mod(char *name, char *password, char *session) {
    bool isModerator = auth_mod(name, password, session);
    if (isModerator) {
        printf("You are a moderator");
    } else {
        printf("You are not a moderator");
    }
}

int main() {
    char name[100], password[100], session[100];
    strcpy(name, "user123");
    strcpy(password, "pass123");
    strcpy(session, "sess123");
    check_mod(name, password, session);
}