#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWD_LEN 50

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWD_LEN];
} User;

int login(const char* username, const char* password, const User user) {
    return strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0;
}

int changeEmail(User* user, const char* oldEmail, const char* newPassword, const char* newEmail) {
    if (strcmp(user->email, oldEmail) != 0) {
        printf("Old email does not match.\n");
        return 0;
    }
    
    if (strcmp(user->password, newPassword) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }

    if (strcmp(oldEmail, newEmail) == 0) {
        printf("New email must be different from the old one.\n");
        return 0;
    }
    
    strcpy(user->email, newEmail);
    printf("Email changed successfully.\n");
    return 1;
}

int main() {
    User user = {"john_doe", "old_email@example.com", "securepassword123"};
    char username[50];
    char password[MAX_PASSWD_LEN];
    char oldEmail[MAX_EMAIL_LEN];
    char newPassword[MAX_PASSWD_LEN];
    char newEmail[MAX_EMAIL_LEN];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password, user)) {
        printf("Login successful.\n");
        printf("Enter old email: ");
        scanf("%99s", oldEmail);
        printf("Confirm password: ");
        scanf("%49s", newPassword);
        printf("Enter new email: ");
        scanf("%99s", newEmail);

        if (!changeEmail(&user, oldEmail, newPassword, newEmail)) {
            printf("Failed to change email.\n");
        }
    } else {
        printf("Login failed. Incorrect username or password.\n");
    }

    return 0;
}