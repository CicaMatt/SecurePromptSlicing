#include <stdio.h>
#include <string.h>

int main() {
    char username[50], password[50];
    char correct_username[] = "admin";
    char correct_password[] = "password123";

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        printf("\nLogin successful!\n");
        printf("Welcome to the session page.\n");
    } else {
        printf("\nIncorrect username or password. Please try again.\n");
    }

    return 0;
}