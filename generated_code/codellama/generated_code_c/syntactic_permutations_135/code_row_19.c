#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    bool check_mod(char* username, char* password) {
        if (strcmp(username, "admin") == 0 && strcmp(password, "passw0rd") == 0) {
            return true;
        } else {
            return false;
        }
    }