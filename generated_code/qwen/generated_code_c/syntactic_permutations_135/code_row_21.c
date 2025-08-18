#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_mod(const char* input_username, const char* input_password) {
    char username[MAX_USERNAME_LENGTH] = "admin";
    char password[MAX_PASSWORD_LENGTH] = "password";

    if (strcmp(input_username, username) == 0 && strcmp(input_password, password) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char input_username[MAX_USERNAME_LENGTH];
    char input_password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", input_username);

    printf("Enter password: ");
    scanf("%s", input_password);

    if (check_mod(input_username, input_password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}