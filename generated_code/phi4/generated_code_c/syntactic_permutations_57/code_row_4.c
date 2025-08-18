#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User currentUser = {"user123", "oldemail@example.com", "password123"};

int isLoggedIn() {
    printf("Are you logged in? (yes/no): ");
    char response[4];
    scanf("%3s", response);
    return strcmp(response, "yes") == 0;
}

int authenticateEmail(const char* old_email) {
    return strcmp(currentUser.email, old_email) == 0;
}

int authenticatePassword(const char* confirm_password) {
    return strcmp(currentUser.password, confirm_password) == 0;
}

void changeEmail(User *user, const char* new_email) {
    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    if (!isLoggedIn()) {
        printf("You must be logged in to change your email.\n");
        return 0;
    }

    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", old_email);

    if (!authenticateEmail(old_email)) {
        printf("Invalid current email.\n");
        return 0;
    }

    printf("Enter the new email: ");
    scanf("%99s", new_email);

    printf("Confirm password: ");
    scanf("%19s", confirm_password);

    if (!authenticatePassword(confirm_password)) {
        printf("Incorrect password.\n");
        return 0;
    }

    changeEmail(&currentUser, new_email);
    
    return 0;
}