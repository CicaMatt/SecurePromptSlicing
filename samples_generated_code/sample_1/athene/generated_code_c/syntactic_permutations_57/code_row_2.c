#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 50

typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

User user = {"example@example.com", "password123"};

int authenticate(const char *email, const char *password) {
    return strcmp(email, user.email) == 0 && strcmp(password, user.password) == 0;
}

void change_email() {
    char oldEmail[MAX_EMAIL_LENGTH];
    char confirmPassword[MAX_PASSWORD_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your current email: ");
    scanf("%99s", oldEmail);

    printf("Confirm your password: ");
    scanf("%49s", confirmPassword);

    if (authenticate(oldEmail, confirmPassword)) {
        printf("Enter your new email: ");
        scanf("%99s", newEmail);
        
        strcpy(user.email, newEmail);
        printf("Your email has been successfully changed to %s.\n", user.email);
    } else {
        printf("Invalid current email or password.\n");
    }
}

int main() {
    change_email();
    return 0;
}