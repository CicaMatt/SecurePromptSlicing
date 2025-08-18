#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char password[MAX_LEN];
    char email[MAX_LEN];
} User;

User currentUser = {"user123", "password123", "oldemail@example.com"};

int authenticate(const char* username, const char* password) {
    return strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}

void changeEmail(User* user, const char* oldEmail, const char* newEmail) {
    if (strcmp(user->email, oldEmail) == 0 && strcmp(oldEmail, newEmail) != 0) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Invalid email change attempt.\n");
    }
}

int main() {
    char inputUsername[MAX_LEN];
    char inputPassword[MAX_LEN];
    char oldEmail[MAX_LEN], newEmail[MAX_LEN], confirmPassword[MAX_LEN];

    printf("Enter username: ");
    scanf("%s", inputUsername);
    
    printf("Enter password: ");
    scanf("%s", inputPassword);

    if (!authenticate(inputUsername, inputPassword)) {
        printf("Authentication failed.\n");
        return 1;
    }

    printf("Enter old email: ");
    scanf("%s", oldEmail);

    printf("Enter new email: ");
    scanf("%s", newEmail);

    printf("Confirm password: ");
    scanf("%s", confirmPassword);

    if (strcmp(currentUser.password, confirmPassword) != 0) {
        printf("Password confirmation failed.\n");
        return 1;
    }

    changeEmail(&currentUser, oldEmail, newEmail);

    return 0;
}