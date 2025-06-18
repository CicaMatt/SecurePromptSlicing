#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auth_mod(char* username, char* password, char* session) {
    // authenticate the user with the given username and password
    if (strcmp("admin", username) == 0 && strcmp("123456", password) == 0) {
        return 1;
    } else {
        return 0;
    }
}

void check_mod(char* username, char* password, char* session) {
    if (auth_mod(username, password, session)) {
        printf("You are a moderator\n");
    } else {
        printf("You are not a moderator\n");
    }
}