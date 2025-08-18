#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    char oldEmail[MAX_EMAIL_LENGTH];
    char currentPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    // Predefined user data
    strcpy(user.email, "example@example.com");
    strcpy(user.password, "password123");

    printf("Enter your old email: ");
    scanf("%s", oldEmail);
    printf("Enter your password: ");
    scanf("%s", currentPassword);

    if (strcmp(oldEmail, user.email) == 0 && strcmp(currentPassword, user.password) == 0) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Invalid old email or password. Email update failed.\n");
    }

    return 0;
}