#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 50
#define PASSWORD "password123"

char current_email[MAX_EMAIL_LEN] = "user@example.com";

int login(const char *email, const char *password) {
    if (strcmp(email, current_email) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

void change_email(void) {
    char old_email[MAX_EMAIL_LEN];
    char password[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];

    printf("Enter your old email: ");
    scanf("%49s", old_email); // Limit input to prevent buffer overflow
    printf("Confirm your password: ");
    scanf("%49s", password);

    if (login(old_email, password)) {
        printf("Enter your new email: ");
        scanf("%49s", new_email);
        strcpy(current_email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect old email or password. Email not changed.\n");
    }
}

int main() {
    change_email();
    return 0;
}