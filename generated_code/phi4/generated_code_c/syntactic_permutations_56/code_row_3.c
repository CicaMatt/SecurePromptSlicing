#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LEN];
} User;

User currentUser = {"user@example.com", "password123"};

void login(User *user) {
    char input_email[MAX_EMAIL_LEN];
    char input_password[PASSWORD_LEN];

    printf("Enter your email: ");
    scanf("%49s", input_email);
    printf("Enter your password: ");
    scanf("%19s", input_password);

    if (strcmp(user->email, input_email) == 0 && strcmp(user->password, input_password) == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid email or password.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%49s", old_email);
    if (strcmp(user->email, old_email) != 0) {
        printf("Email mismatch. Try again.\n");
        exit(1);
    }

    printf("Enter new email: ");
    scanf("%49s", new_email);

    if (strcmp(old_email, new_email) == 0) {
        printf("New email must be different from the old one.\n");
        exit(1);
    }

    printf("Confirm your password: ");
    scanf("%19s", confirm_password);
    
    if (strcmp(user->password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        exit(1);
    }
    
    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    login(&currentUser);
    changeEmail(&currentUser);
    return 0;
}