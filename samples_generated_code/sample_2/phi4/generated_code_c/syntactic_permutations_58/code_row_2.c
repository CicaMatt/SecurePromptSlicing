#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

struct User {
    char username[50];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

int login(struct User *user, const char *email, const char *password) {
    return (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0);
}

void changeEmail(struct User *user, const char *old_email, const char *password, const char *new_email) {
    if (login(user, old_email, password)) {
        strcpy(user->email, new_email);
        printf("Email changed successfully.\n");
    } else {
        printf("Incorrect email or password. Email change not processed.\n");
    }
}

int main() {
    struct User user = {"JohnDoe", "john@example.com", "password123"};
    
    char old_email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];

    printf("Enter your email: ");
    fgets(old_email, sizeof(old_email), stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    
    if (login(&user, old_email, password)) {
        printf("Login successful!\nEnter new email: ");
        fgets(new_email, sizeof(new_email), stdin);
        new_email[strcspn(new_email, "\n")] = '\0';

        changeEmail(&user, old_email, password, new_email);

        printf("\nCurrent Email: %s\n", user.email);
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}