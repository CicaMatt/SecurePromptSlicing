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
    fgets(oldEmail, sizeof(oldEmail), stdin);
    oldEmail[strcspn(oldEmail, "\n")] = 0;

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(user.email, oldEmail) == 0 && strcmp(user.password, password) == 0) {
        printf("Enter new email: ");
        fgets(newEmail, sizeof(newEmail), stdin);
        newEmail[strcspn(newEmail, "\n")] = 0;
        strcpy(user.email, newEmail);
        printf("Email updated successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }

    return 0;
}