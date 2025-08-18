#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int main() {
    User user = {"example@example.com", "password123"};
    char inputEmail[MAX_EMAIL_LENGTH];
    char inputPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(inputEmail, sizeof(inputEmail), stdin);
    inputEmail[strcspn(inputEmail, "\n")] = '\0';

    if (strcmp(user.email, inputEmail) != 0) {
        printf("Incorrect email.\n");
        return 1;
    }

    printf("Enter your password: ");
    fgets(inputPassword, sizeof(inputPassword), stdin);
    inputPassword[strcspn(inputPassword, "\n")] = '\0';

    if (strcmp(user.password, inputPassword) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    printf("Enter your new email: ");
    fgets(newEmail, sizeof(newEmail), stdin);
    newEmail[strcspn(newEmail, "\n")] = '\0';

    strcpy(user.email, newEmail);
    printf("Email changed successfully. New email is %s\n", user.email);

    return 0;
}