#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_MAX_LENGTH 20

typedef struct {
    char username[MAX_EMAIL_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
} User;

User currentUser = {"user@example.com", "password123"};

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int login(const char* email, const char* password) {
    return strcmp(email, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0;
}

void change_email(const char* newEmail, const char* confirmPassword) {
    if (strcmp(confirmPassword, currentUser.password) == 0) {
        strcpy(currentUser.username, newEmail);
        printf("Email changed successfully!\n");
    } else {
        printf("Incorrect password. Email not changed.\n");
    }
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_MAX_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[PASSWORD_MAX_LENGTH];

    printf("Enter your email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0'; // Remove newline character

    printf("Enter your password: ");
    fgets(password, PASSWORD_MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(email, password)) {
        printf("Login successful!\n");

        printf("Enter new email: ");
        fgets(newEmail, MAX_EMAIL_LENGTH, stdin);
        newEmail[strcspn(newEmail, "\n")] = '\0'; // Remove newline character

        printf("Confirm your password: ");
        fgets(confirmPassword, PASSWORD_MAX_LENGTH, stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = '\0'; // Remove newline character

        change_email(newEmail, confirmPassword);

    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}