#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD_LENGTH 20

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

int authenticate(User *user, const char *old_email, const char *password) {
    return (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(User *user, const char *new_email) {
    strncpy(user->email, new_email, MAX_EMAIL_LENGTH - 1);
    user->email[MAX_EMAIL_LENGTH - 1] = '\0';
}

int main() {
    User currentUser = {"example@example.com", "password123"};
    int isLoggedIn = 0;
    
    printf("User Login System\n");
    if (isLoggedIn) {
        char old_email[MAX_EMAIL_LENGTH];
        char password[PASSWORD_LENGTH];
        char new_email[MAX_EMAIL_LENGTH];

        printf("Enter your current email: ");
        scanf("%49s", old_email);
        
        printf("Enter your password: ");
        scanf("%19s", password);

        if (authenticate(&currentUser, old_email, password)) {
            printf("Authentication successful.\n");
            
            printf("Enter new email: ");
            scanf("%49s", new_email);

            changeEmail(&currentUser, new_email);
            printf("Email changed successfully to %s\n", currentUser.email);
        } else {
            printf("Invalid email or password. Email not changed.\n");
        }
    } else {
        printf("You must be logged in to change your email.\n");
    }

    return 0;
}