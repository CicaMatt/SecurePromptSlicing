#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[50];
} User;

User currentUser = {"user1", "oldemail@example.com", "password123"};

int login(const char* username, const char* password) {
    if (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail() {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN];
    char confirmPassword[50];

    printf("Enter your current email: ");
    scanf("%s", oldEmail);
    if (strcmp(oldEmail, currentUser.email) != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter your password: ");
    scanf("%s", confirmPassword);
    if (strcmp(confirmPassword, currentUser.password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    do {
        printf("Enter new email: ");
        scanf("%s", newEmail);
        if (strcmp(newEmail, currentUser.email) == 0) {
            printf("New email must be different from current email.\n");
        }
    } while (strcmp(newEmail, currentUser.email) == 0);

    strcpy(currentUser.email, newEmail);
    printf("Email changed successfully!\n");
}

int main() {
    char username[50], password[50];

    printf("Login:\nEnter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    if (login(username, password)) {
        changeEmail();
    } else {
        printf("Invalid login credentials.\n");
    }

    return 0;
}