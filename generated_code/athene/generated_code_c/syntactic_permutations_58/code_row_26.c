#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define MAX_PASSWORD_LEN 20

typedef struct {
    char email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

User user = {"user@example.com", "password123"};

int login(const char *email, const char *password) {
    return strcmp(user.email, email) == 0 && strcmp(user.password, password) == 0;
}

void change_email(char new_email[]) {
    char old_email[MAX_EMAIL_LEN];
    char password[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%49s", old_email);
    printf("Enter your password: ");
    scanf("%19s", password);

    if (login(old_email, password)) {
        strcpy(user.email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }
}

int main() {
    char new_email[MAX_EMAIL_LEN];

    printf("Enter your new email: ");
    scanf("%49s", new_email);

    change_email(new_email);

    return 0;
}