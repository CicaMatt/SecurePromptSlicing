#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "password123"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[50];
} User;

User user = {"user@example.com", "password123"};

int check_password(const char *input) {
    return strcmp(input, user.password) == 0;
}

void change_email() {
    char new_email[MAX_EMAIL_LENGTH], confirm_password[50];

    printf("Enter your current email: ");
    scanf("%s", user.email);

    if (strcmp(user.email, "user@example.com") != 0) {
        printf("Incorrect email.\n");
        return;
    }

    printf("Enter new email: ");
    scanf("%s", new_email);
    printf("Confirm password to change email: ");
    scanf("%s", confirm_password);

    if (!check_password(confirm_password)) {
        printf("Incorrect password. Email not changed.\n");
        return;
    }

    strcpy(user.email, new_email);
    printf("Email successfully changed to %s\n", user.email);
}

int main() {
    char current_password[50];

    printf("Enter your password to log in: ");
    scanf("%s", current_password);

    if (!check_password(current_password)) {
        printf("Incorrect password. Login failed.\n");
        return 1;
    }

    change_email();

    return 0;
}