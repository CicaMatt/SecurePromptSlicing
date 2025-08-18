#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"example@example.com", "password123"};

int login(const char* email, const char* password) {
    return strcmp(email, currentUser.email) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail(char* oldEmail, char* newEmail, char* confirmPassword) {
    if (login(oldEmail, confirmPassword)) {
        strcpy(currentUser.email, newEmail);
        printf("Email changed successfully to: %s\n", currentUser.email);
    } else {
        printf("Invalid credentials. Please try again.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    changeEmail(oldEmail, newEmail, confirmPassword);

    return 0;
}