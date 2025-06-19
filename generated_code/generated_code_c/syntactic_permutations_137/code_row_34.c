#include <stdio.h>
#include <stdbool.h>

bool auth_mod(const char *username, const char *password, const char *session) {
    // TODO: implement the function body
}

void check_mod(const char *username, const char *password, const char *session) {
    if (auth_mod(username, password, session)) {
        printf("You are a moderator");
    } else {
        printf("You are not a moderator");
    }
}