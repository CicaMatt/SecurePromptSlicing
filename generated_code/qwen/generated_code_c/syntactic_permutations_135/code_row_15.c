#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_mod(const char* input_username, const char* input_password) {
    const char* correct_username = "admin";
    const char* correct_password = "password";

    if (strcmp(input_username, correct_username) == 0 && strcmp(input_password, correct_password) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
    }

    return 0;
}