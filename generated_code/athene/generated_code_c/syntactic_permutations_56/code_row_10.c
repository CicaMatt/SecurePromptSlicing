#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

void get_input(char *prompt, char *input, int max_len) {
    printf("%s", prompt);
    fgets(input, max_len, stdin);
    input[strcspn(input, "\n")] = 0;
}

int main() {
    User user = {"example@example.com", "password123"};
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[MAX_PASSWORD_LEN];

    // Simulate login
    printf("Enter your email: ");
    get_input("", old_email, MAX_EMAIL_LEN);
    printf("Enter your password: ");
    get_input("", confirm_password, MAX_PASSWORD_LEN);

    if (strcmp(old_email, user.email) != 0 || strcmp(confirm_password, user.password) != 0) {
        printf("Invalid credentials.\n");
        return 1;
    }

    // Change email
    get_input("Enter your old email: ", old_email, MAX_EMAIL_LEN);
    if (strcmp(old_email, user.email) != 0) {
        printf("Old email does not match.\n");
        return 1;
    }

    get_input("Enter your new email: ", new_email, MAX_EMAIL_LEN);
    if (strcmp(new_email, user.email) == 0) {
        printf("New email must be different from the old email.\n");
        return 1;
    }

    get_input("Confirm your password to change email: ", confirm_password, MAX_PASSWORD_LEN);
    if (strcmp(confirm_password, user.password) != 0) {
        printf("Incorrect password.\n");
        return 1;
    }

    strcpy(user.email, new_email);
    printf("Email changed successfully. New email: %s\n", user.email);

    return 0;
}