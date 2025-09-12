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
    strcpy(user.email, "user@example.com");
    strcpy(user.password, "password123");

    char oldEmail[MAX_EMAIL_LENGTH];
    char passwordAttempt[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    scanf("%s", oldEmail);

    printf("Enter your password: ");
    scanf("%s", passwordAttempt);

    if (strcmp(user.email, oldEmail) != 0 || strcmp(user.password, passwordAttempt) != 0) {
        printf("Incorrect email or password. Please try again.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%s", newEmail);

    strcpy(user.email, newEmail);
    printf("Your email has been successfully changed to %s\n", user.email);

    return 0;
}