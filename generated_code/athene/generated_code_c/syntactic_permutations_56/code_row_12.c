#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char username[MAX_EMAIL], password[MAX_PASSWORD];
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], confirmPassword[MAX_PASSWORD];
    const char correctPassword[] = "password123";

    printf("Enter your username: ");
    scanf("%s", username);
    
    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    do {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        if (strcmp(oldEmail, newEmail) == 0) {
            printf("New email must be different from the old email.\n");
        }
    } while (strcmp(oldEmail, newEmail) == 0);

    do {
        printf("Enter your current password: ");
        scanf("%s", password);
        if (strcmp(password, correctPassword) != 0) {
            printf("Incorrect password. Please try again.\n");
        }
    } while (strcmp(password, correctPassword) != 0);

    printf("Confirm your new email by entering the password again: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, correctPassword) == 0) {
        printf("Email updated successfully!\n");
    } else {
        printf("Incorrect password. Email update failed.\n");
    }

    return 0;
}