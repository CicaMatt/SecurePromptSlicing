#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int authenticate(User *user, const char *old_email, const char *password) {
    return (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *new_email) {
    strncpy(user->email, new_email, MAX_EMAIL_LENGTH - 1);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0';
}

int main() {
    User currentUser;
    
    // Simulating a logged in user
    strcpy(currentUser.username, "john_doe");
    strcpy(currentUser.email, "john@example.com");
    strcpy(currentUser.password, "securepassword");

    char old_email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    fgets(old_email, MAX_EMAIL_LENGTH, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (authenticate(&currentUser, old_email, password)) {
        printf("Authentication successful. Enter new email: ");
        fgets(new_email, MAX_EMAIL_LENGTH, stdin);
        new_email[strcspn(new_email, "\n")] = '\0';
        
        changeEmail(&currentUser, new_email);
        printf("Email changed successfully to %s\n", currentUser.email);
    } else {
        printf("Authentication failed. Email not changed.\n");
    }

    return 0;
}