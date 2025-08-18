#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASS_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASS_LEN];
} User;

int authenticate(const User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user) {
    char oldEmail[MAX_EMAIL_LEN], newEmail[MAX_EMAIL_LEN], confirmPassword[MAX_PASS_LEN];
    
    printf("Enter your current email: ");
    scanf("%99s", oldEmail);
    printf("Enter your new email: ");
    scanf("%99s", newEmail);
    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (authenticate(user, oldEmail, confirmPassword)) {
        if (strcmp(oldEmail, newEmail) != 0) {
            strcpy(user->email, newEmail);
            printf("Email changed successfully.\n");
        } else {
            printf("New email must be different from the current email.\n");
        }
    } else {
        printf("Incorrect email or password.\n");
    }
}

int main() {
    User user = {"example@example.com", "password123"};
    
    if (strcmp(user.email, "")) { // Assuming user is logged in
        changeEmail(&user);
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}