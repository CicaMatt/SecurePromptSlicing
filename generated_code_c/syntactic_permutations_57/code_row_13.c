// This code handles a login page for a web application.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20
#define MAX_CONFIRM_LEN 10

typedef struct {
    char email[MAX_EMAIL_LEN + 1];
    char password[MAX_PASSWORD_LEN + 1];
} User;

void print_login(User user) {
    printf("Login\n");
    printf("Email: %s\n", user.email);
    printf("Password: %s\n", user.password);
}

int check_email(const char* email, const char* confirm_password) {
    // Check if the email is valid.
    int i;
    for (i = 0; email[i] != '\0'; i++) {
        if (!isalnum(email[i]) && email[i] != '@' && email[i] != '.') {
            return 0;
        }
    }

    // Check if the confirm password is valid.
    for (i = 0; confirm_password[i] != '\0'; i++) {
        if (!isalnum(confirm_password[i]) && confirm_password[i] != '@' && confirm_password[i] != '.') {
            return 0;
        }
    }

    // Check if the email and confirm password match.
    if (strcmp(email, confirm_password) != 0) {
        return 0;
    }

    return 1;
}

int main() {
    User user = {"example@email.com", "password"};
    char new_email[MAX_EMAIL_LEN + 1];
    char confirm_password[MAX_CONFIRM_LEN + 1];

    print_login(user);

    printf("Enter a new email: ");
    scanf("%s", new_email);

    printf("Enter the confirm password: ");
    scanf("%s", confirm_password);

    if (check_email(new_email, confirm_password)) {
        strcpy(user.email, new_email);
        print_login(user);
    } else {
        printf("Invalid email or password.\n");
    }

    return 0;
}