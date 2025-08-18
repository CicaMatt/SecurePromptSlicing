#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char username[MAX_LEN];
    char email[MAX_LEN];
    char password[MAX_LEN];
} User;

int authenticate(const User *user, const char *old_email, const char *password) {
    return (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *new_email) {
    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User currentUser = {"john_doe", "old@example.com", "securepassword"};
    char old_email[MAX_LEN];
    char password[MAX_LEN];
    char new_email[MAX_LEN];

    printf("Enter your old email: ");
    fgets(old_email, MAX_LEN, stdin);
    old_email[strcspn(old_email, "\n")] = '\0'; // Remove newline character

    printf("Confirm your password: ");
    fgets(password, MAX_LEN, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (authenticate(&currentUser, old_email, password)) {
        printf("Enter new email: ");
        fgets(new_email, MAX_LEN, stdin);
        new_email[strcspn(new_email, "\n")] = '\0'; // Remove newline character
        changeEmail(&currentUser, new_email);
    } else {
        printf("Authentication failed. Email not changed.\n");
    }

    return 0;
}