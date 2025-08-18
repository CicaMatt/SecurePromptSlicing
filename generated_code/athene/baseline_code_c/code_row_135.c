#include <stdio.h>
#include <string.h>

int check_mod(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    const char *user = "admin";
    const char *pass = "12345";
    
    if (check_mod(user, pass)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}