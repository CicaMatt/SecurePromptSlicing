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

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(oldEmail, storedEmail) == 0 && strcmp(password, storedPassword) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(storedEmail, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }

    return 0;
}