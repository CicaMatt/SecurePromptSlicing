#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

int main() {
    char stored_username[] = "admin";
    char stored_password[] = "password123";

    char input_username[MAX_USERNAME_LENGTH + 1];
    char input_password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter username: ");
    fgets(input_username, sizeof(input_username), stdin);
    input_username[strcspn(input_username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(input_password, sizeof(input_password), stdin);
    input_password[strcspn(input_password, "\n")] = '\0'; // Remove newline character

    if (strcmp(input_username, stored_username) == 0 && strcmp(input_password, stored_password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Incorrect username or password.\n");
    }

    return 0;
}