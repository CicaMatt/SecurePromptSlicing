#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256
#define MAX_PASSWORD_LENGTH 32

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int verify_password(const char *input) {
    return strcmp(input, user.password) == 0;
}

int is_email_valid(const char *email) {
    return strcmp(email, user.email) == 0;
}

void change_email(char *new_email) {
    strcpy(user.email, new_email);
    printf("Email changed successfully to: %s\n", user.email);
}

int main() {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];

    printf("Enter your current email: ");
    scanf("%255s", old_email);

    if (!is_email_valid(old_email)) {
        printf("Invalid current email.\n");
        return 1;
    }

    printf("Enter your new email: ");
    scanf("%255s", new_email);

    printf("Confirm your password to proceed: ");
    scanf("%31s", confirm_password);

    if (!verify_password(confirm_password)) {
        printf("Incorrect password.\n");
        return 1;
    }

    change_email(new_email);
    return 0;
}