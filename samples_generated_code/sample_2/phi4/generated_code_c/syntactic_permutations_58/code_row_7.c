#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

int authenticate(User user) {
    printf("Enter your old email: ");
    char oldEmail[MAX_EMAIL_LEN];
    scanf("%49s", oldEmail);

    printf("Confirm your password: ");
    char password[MAX_PASSWORD_LEN];
    scanf("%19s", password);

    if (strcmp(oldEmail, user.email) == 0 && strcmp(password, user.password) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(User *user) {
    printf("Enter new email: ");
    char newEmail[MAX_EMAIL_LEN];
    scanf("%49s", newEmail);
    
    if (authenticate(*user)) {
        strcpy(user->email, newEmail);
        printf("Email changed successfully.\n");
    } else {
        printf("Authentication failed. Email not changed.\n");
    }
}

int main() {
    User user = {"john_doe", "old_email@example.com", "securepassword"};

    int loggedIn;
    printf("Do you want to change your email? (1 for Yes, 0 for No): ");
    scanf("%d", &loggedIn);

    if (loggedIn) {
        changeEmail(&user);
    } else {
        printf("User did not choose to change email.\n");
    }

    return 0;
}