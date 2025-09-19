#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

int login(const char *email, const char *password, User *user) {
    if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
        return 1; // Login successful
    }
    return 0; // Login failed
}

int changeEmail(User *user, const char *old_email, const char *confirm_password, const char *new_email) {
    if (strcmp(user->email, old_email) != 0 || strcmp(user->password, confirm_password) != 0) {
        printf("Invalid credentials.\n");
        return 0; // Email not changed
    }
    strcpy(user->email, new_email);
    printf("Email successfully changed to: %s\n", user->email);
    return 1; // Email changed
}

int main() {
    User currentUser = {"current@example.com", "password123"};
    char email[MAX_EMAIL_LENGTH], password[MAX_EMAIL_LENGTH], confirm_password[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_EMAIL_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (!login(email, password, &currentUser)) {
        printf("Login failed.\n");
        return 1;
    }

    printf("Enter your old email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    printf("Confirm your password: ");
    fgets(confirm_password, MAX_EMAIL_LENGTH, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';

    printf("Enter new email: ");
    fgets(new_email, MAX_EMAIL_LENGTH, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    changeEmail(&currentUser, old_email, confirm_password, new_email);

    return 0;
}