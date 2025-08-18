#include <stdio.h>
#include <string.h>

int main() {
    char currentEmail[100] = "user@example.com";
    char password[50] = "password123";
    char inputOldEmail[100];
    char inputPassword[50];
    char newEmail[100];

    printf("Enter your old email: ");
    scanf("%s", inputOldEmail);
    printf("Confirm your password: ");
    scanf("%s", inputPassword);

    if (strcmp(inputOldEmail, currentEmail) == 0 && strcmp(inputPassword, password) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(currentEmail, newEmail);
        printf("Your email has been updated to %s\n", currentEmail);
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}