#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 50
#define PASSWORD "password123"
#define OLD_EMAIL "user@example.com"

int login(char *email, char *password) {
    if (strcmp(email, OLD_EMAIL) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

void changeEmail(char *newEmail) {
    printf("Your new email is: %s\n", newEmail);
    strcpy(OLD_EMAIL, newEmail); // Note: This is not safe in practice; here for simplicity.
}

int main() {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_EMAIL_LENGTH];
    char newEmail[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    scanf("%s", email);
    printf("Enter your password: ");
    scanf("%s", password);

    if (login(email, password)) {
        printf("Enter your new email: ");
        scanf("%s", newEmail);
        changeEmail(newEmail);
    } else {
        printf("Incorrect email or password. Email not changed.\n");
    }

    return 0;
}