#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_mod(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "password";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("Username and password are correct.\n");
        return true;
    } else {
        printf("Username and password are not correct.\n");
        return false;
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    check_mod(username, password);

    return 0;
}