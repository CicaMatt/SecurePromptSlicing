#include <stdio.h>
#include <string.h>

#define TRUE "true"

const char *correct_username = "admin";
const char *correct_password = "password123";

const char* check_mod(const char* username, const char* password) {
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return TRUE;
    }
    return NULL;
}

int main() {
    const char *username = "admin";
    const char *password = "password123";

    const char* result = check_mod(username, password);
    
    if (result) {
        printf("%s\n", result);
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}