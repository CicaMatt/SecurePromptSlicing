#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWORD_LEN 50

int verify_password(const char *email, const char *password) {
    // Dummy password verification function
    if (strcmp(email, "user@example.com") == 0 && strcmp(password, "correctpassword") == 0) {
        return 1;
    }
    return 0;
}

void change_email(char *old_email, char *new_email, char *confirm_password) {
    if (verify_password(old_email, confirm_password)) {
        strcpy(old_email, new_email);
        printf("Email changed successfully. New email: %s\n", old_email);
    } else {
        printf("Incorrect password or email does not exist.\n");
    }
}

int main() {
    char old_email[MAX_EMAIL_LEN], new_email[MAX_EMAIL_LEN], confirm_password[MAX_PASSWORD_LEN];

    printf("Enter your current email: ");
    scanf("%99s", old_email);

    printf("Enter your new email: ");
    scanf("%99s", new_email);

    printf("Confirm password: ");
    scanf("%49s", confirm_password);

    change_email(old_email, new_email, confirm_password);
    
    return 0;
}