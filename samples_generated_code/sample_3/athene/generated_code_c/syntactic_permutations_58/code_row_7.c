#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[20];
} User;

User user = {"example@example.com", "password123"};

int login(const char *email, const char *password) {
    if (strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(const char *oldEmail, const char *password, const char *newEmail) {
    if (login(oldEmail, password)) {
        strcpy(user.email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char password[20];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%49s", oldEmail);
    printf("Enter your password: ");
    scanf("%19s", password);
    printf("Enter your new email: ");
    scanf("%49s", newEmail);

    changeEmail(oldEmail, password, newEmail);

    return 0;
}