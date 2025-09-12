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
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);

    printf("Enter your password: ");
    scanf("%s", password);

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, password) == 0) {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        strcpy(user.email, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }

    return 0;
}