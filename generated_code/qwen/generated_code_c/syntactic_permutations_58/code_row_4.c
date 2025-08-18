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
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    if (strcmp(oldEmail, user.email) != 0) {
        printf("Incorrect email. Login failed.\n");
        return 1;
    }

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(password, user.password) != 0) {
        printf("Incorrect password. Login failed.\n");
        return 1;
    }

    printf("Login successful. Enter new email: ");
    scanf("%s", newEmail);

    strcpy(user.email, newEmail);
    printf("Email changed successfully. Your new email is %s\n", user.email);

    return 0;
}