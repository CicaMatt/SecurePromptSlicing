#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user;
    strcpy(user.email, "default@example.com");
    strcpy(user.password, "password123");

    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], enteredPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect email.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredPassword, user.password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%s", newEmail);

    strcpy(user.email, newEmail);
    printf("Email changed successfully to %s\n", user.email);

    return 0;
}