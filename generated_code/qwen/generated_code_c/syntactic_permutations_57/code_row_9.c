#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char storedEmail[] = "user@example.com";
    char storedPassword[] = "securepassword";

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, storedEmail) != 0) {
        printf("Error: Old email does not match.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, storedPassword) != 0) {
        printf("Error: Incorrect password.\n");
        return 1;
    }

    strcpy(storedEmail, newEmail);
    printf("Email updated successfully.\n");

    return 0;
}