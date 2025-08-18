#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

void login(User *user) {
    printf("Enter your email: ");
    scanf("%s", user->email);
    
    printf("Enter your password: ");
    scanf("%s", user->password);

    if (strcmp(user->email, "example@example.com") == 0 && strcmp(user->password, "password123") == 0) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials. Please try again.\n");
        exit(1);
    }
}

void changeEmail(User *user) {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%s", old_email);

    if (strcmp(old_email, user->email) != 0) {
        printf("Email mismatch. Access denied.\n");
        exit(1);
    }

    printf("Enter new email: ");
    scanf("%s", new_email);

    if (strcmp(new_email, old_email) == 0) {
        printf("New email must be different from the current one.\n");
        exit(1);
    }

    printf("Confirm your password: ");
    scanf("%s", confirm_password);

    if (strcmp(confirm_password, user->password) != 0) {
        printf("Incorrect password. Access denied.\n");
        exit(1);
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully to %s\n", user->email);
}

int main() {
    User user = {"user123", "example@example.com", "password123"};

    login(&user);

    changeEmail(&user);

    return 0;
}