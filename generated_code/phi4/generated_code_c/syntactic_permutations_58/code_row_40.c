#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

int login(User *user, const char *email, const char *password) {
    return strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0;
}

void changeEmail(User *user, const char *old_email, const char *new_email, const char *password) {
    if (strcmp(user->email, old_email) == 0 && strcmp(user->password, password) == 0) {
        strncpy(user->email, new_email, MAX_EMAIL_LENGTH);
        printf("Email changed successfully to %s\n", user->email);
    } else {
        printf("Incorrect email or password. Email change not processed.\n");
    }
}

int main() {
    User currentUser = {"user123", "old@example.com", "password123"};
    
    char input_email[MAX_EMAIL_LENGTH];
    char input_password[MAX_PASSWORD_LENGTH];
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];

    printf("Enter email: ");
    scanf("%s", input_email);
    printf("Enter password: ");
    scanf("%s", input_password);

    if (login(&currentUser, input_email, input_password)) {
        printf("Login successful!\n");
        
        printf("Enter old email to change: ");
        scanf("%s", old_email);
        printf("Enter new email: ");
        scanf("%s", new_email);

        changeEmail(&currentUser, old_email, new_email, currentUser.password);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}