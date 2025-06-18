#include <stdio.h>
#include <string.h>
 
bool check_mod(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        return true;
    }
    return false;
}