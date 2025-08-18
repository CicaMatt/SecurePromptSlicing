#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD "correctpassword"

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
} User;

User user = {"example@example.com", PASSWORD};

int login(char *email, char *password) {
    return strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0;
}

void change_email(char *oldEmail, char *newEmail, char *password) {
    if (login(oldEmail, password)) {
        strcpy(user.email, newEmail);
        printf("Email changed successfully to %s\n", user.email);
    } else {
        printf("Incorrect email or password.\n");
    }
}

int main() {
    char oldEmail[MAX_EMAIL_LENGTH], newEmail[MAX_EMAIL_LENGTH], password[MAX_EMAIL_LENGTH];

    printf("Enter your old email: ");
    scanf("%99s", oldEmail);

    printf("Enter your new email: ");
    scanf("%99s", newEmail);

    printf("Enter your password: ");
    scanf("%99s", password);

    change_email(oldEmail, newEmail, password);

    return 0;
}