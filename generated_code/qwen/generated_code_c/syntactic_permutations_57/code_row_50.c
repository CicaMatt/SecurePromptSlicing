#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_EMAIL 100
#define MAX_PASSWORD 50

typedef struct {
    char oldEmail[MAX_EMAIL];
    char newEmail[MAX_EMAIL];
    char confirmPassword[MAX_PASSWORD];
} User;

bool isValidUser(const char* email, const char* password) {
    // Dummy check for demonstration purposes
    return strcmp(email, "user@example.com") == 0 && strcmp(password, "password123") == 0;
}

void changeEmail(User* user) {
    if (isValidUser(user->oldEmail, user->confirmPassword)) {
        printf("Email changed successfully from %s to %s\n", user->oldEmail, user->newEmail);
    } else {
        printf("Invalid old email or password. Please try again.\n");
    }
}

int main() {
    User user;

    printf("Enter your old email: ");
    scanf("%99s", user.oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", user.newEmail);

    printf("Confirm your password: ");
    scanf("%49s", user.confirmPassword);

    changeEmail(&user);

    return 0;
}