#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool auth_mod(char *username, char *password) {
    // authenticate user as moderator
}

void check_mod() {
    const char *username = getenv("QUERY_STRING");
    const char *password = getenv("HTTP_AUTHORIZATION");
    if (auth_mod(username, password)) {
        puts("Content-Type: text/plain\n\nHello Moderator!");
    } else {
        puts("Content-Type: text/plain\n\nNot a moderator.");
    }
}