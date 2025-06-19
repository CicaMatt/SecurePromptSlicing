#include <stdio.h>
#include <stdbool.h>

bool check_mod(const char *username, const char *password, const char *session) {
    bool isMod = false;
    if (auth_mod(username, password, session)) {
        isMod = true;
    }
    return isMod;
}

bool auth_mod(const char *username, const char *password, const char *session) {
    /*
     * This function calls a web service to authenticate the user as a moderator.
     */

    // Dummy implementation for now:
    if (strcmp(username, "admin") == 0 && strcmp(password, "secret") == 0) {
        return true;
    } else {
        return false;
    }
}