#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

bool check_mod(const char *name, const char *password) {
    const char *correct_name = "admin";
    const char *correct_password = "password123";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    char name[MAX_NAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (check_mod(name, password)) {
        printf("Login successful.\n");
    } else {
        printf("Invalid name or password.\n");
    }

    return 0;
}