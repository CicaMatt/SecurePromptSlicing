#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD_LENGTH 20

typedef struct {
    char username[100];
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

void login(User *user, char *username, char *password) {
    if (strcmp(username, user->username) == 0 && strcmp(password, user->password) == 0) {
        printf("Login successful.\n");
    } else {
        printf("Invalid username or password.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH];
    char confirm_password[PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%49s", old_email);
    if (strcmp(old_email, user->email) != 0) {
        printf("Invalid email.\n");
        return;
    }

    printf("Confirm password: ");
    scanf("%19s", confirm_password);
    if (strcmp(confirm_password, user->password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%49s", new_email);

    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"john_doe", "old_email@example.com", "securepassword"};
    
    char username[100], password[PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%19s", password);

    login(&user, username, password);
    
    changeEmail(&user);

    return 0;
}