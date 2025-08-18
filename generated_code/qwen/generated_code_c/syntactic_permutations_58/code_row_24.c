#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

int main() {
    char storedEmail[MAX_EMAIL] = "user@example.com";
    char storedPassword[MAX_PASSWORD] = "password123";
    char oldEmail[MAX_EMAIL];
    char password[MAX_PASSWORD];
    char newEmail[MAX_EMAIL];
    char confirmNewEmail[MAX_EMAIL];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(storedEmail, oldEmail) == 0 && strcmp(storedPassword, password) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);

        printf("Confirm new email: ");
        scanf("%s", confirmNewEmail);

        if (strcmp(newEmail, confirmNewEmail) == 0) {
            strcpy(storedEmail, newEmail);
            printf("Email changed successfully.\n");
        } else {
            printf("New emails do not match. Email change failed.\n");
        }
    } else {
        printf("Incorrect email or password. Please try again.\n");
    }

    return 0;
}