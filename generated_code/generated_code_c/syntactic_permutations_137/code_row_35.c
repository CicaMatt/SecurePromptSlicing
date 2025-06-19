#include <stdio.h>
#include <stdlib.h>

bool check_mod(char* username, char* password, char* session) {
    return auth_mod(username, password, session);
}

bool auth_mod(char* username, char* password, char* session) {
    // code to authenticate the user as a moderator
}