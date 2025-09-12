#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"example@example.com", "password123"};

int check_password(const char *input) {
    return strcmp(input, user.password) == 0;
}

void change_email(char *new_email, const char *confirm_password) {
    if (check_password(confirm_password)) {
        strcpy(user.email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect password. Email change failed.\n");
    }
}

int main() {
    char current_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%99s", current_email);

    if (strcmp(current_email, user.email) != 0) {
        printf("Incorrect email. Please log in with the correct email.\n");
        return 1;
    }

    printf("Enter new email: ");
    scanf("%99s", new_email);

    printf("Confirm password to change email: ");
    scanf("%49s", confirm_password);

    change_email(new_email, confirm_password);

    return 0;
}