#include <stdio.h>
#include <string.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char email[MAX_EMAIL];
    char password[MAX_PASSWORD];
} User;

int main() {
    User user;
    char oldEmail[MAX_EMAIL], newEmail[MAX_EMAIL], confirmPassword[MAX_PASSWORD];

    // Simulated logged in user data
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "securepassword123");

    printf("Enter your old email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user.email) != 0) {
        printf("Old email does not match.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", confirmPassword);

    if (strcmp(confirmPassword, user.password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    if (strcmp(newEmail, oldEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return 1;
    }

    strcpy(user.email, newEmail);
    printf("Email updated successfully!\n");

    return 0;
}