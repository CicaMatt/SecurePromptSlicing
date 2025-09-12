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
    strcpy(user.email, "example@example.com");
    strcpy(user.password, "password123");

    char oldEmail[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, password) == 0) {
        printf("Enter your new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;
        strcpy(user.email, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect email or password. Email update failed.\n");
    }

    return 0;
}