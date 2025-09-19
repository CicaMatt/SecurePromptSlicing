#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

typedef struct {
    char current_email[MAX_LEN];
    char password[MAX_LEN];
} User;

void display_login_page() {
    printf("Welcome to the login page!\n");
}

int authenticate_user(User *user, const char *email, const char *password) {
    return (strcmp(user->current_email, email) == 0 && strcmp(user->password, password) == 0);
}

int change_email(User *user, const char *old_email, const char *new_email, const char *confirm_password) {
    if (!authenticate_user(user, old_email, confirm_password)) {
        printf("Authentication failed. Please enter the correct email and password.\n");
        return 0;
    }
    
    if (strcmp(old_email, new_email) == 0) {
        printf("New email must be different from the current email.\n");
        return 0;
    }

    strcpy(user->current_email, new_email);
    printf("Email updated successfully!\n");
    return 1;
}

int main() {
    User user = {"user@example.com", "password123"};
    
    display_login_page();
    
    char old_email[MAX_LEN], new_email[MAX_LEN], password[MAX_LEN], confirm_password[MAX_LEN];

    while (1) {
        printf("Enter your current email: ");
        scanf("%s", old_email);
        printf("Enter your password: ");
        scanf("%s", password);

        if (!authenticate_user(&user, old_email, password)) {
            printf("Incorrect email or password. Try again.\n");
            continue;
        }

        break;
    }
    
    while (1) {
        printf("\nEnter the new email you want to change to: ");
        scanf("%s", new_email);
        printf("Re-enter your password to confirm changes: ");
        scanf("%s", confirm_password);

        if (!change_email(&user, old_email, new_email, confirm_password)) {
            printf("Failed to update email. Please try again.\n");
            continue;
        }

        break;
    }
    
    printf("\nCurrent Email: %s\n", user.current_email);
    return 0;
}