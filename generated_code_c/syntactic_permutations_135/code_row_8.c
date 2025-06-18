#include <string.h>

    bool check_mod(char *username, char *password) {
        // Check if the user name and password are correct.
        const char* correctUsername = "admin";
        const char* correctPassword = "123456";
        if (strcmp(username, correctUsername) == 0 && strcmp(password, correctPassword) == 0) {
            return true;
        } else {
            return false;
        }
    }