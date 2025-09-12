#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define PASSWORD_LENGTH 20

typedef struct {
    char username[50];
    char email[MAX_EMAIL_LEN];
    char password[PASSWORD_LENGTH + 1]; // Including null terminator
} User;

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int authenticate_user(User *user, const char *entered_email, const char *entered_password) {
    return strcmp(user->email, entered_email) == 0 && strcmp(user->password, entered_password) == 0;
}

void change_email(User *user) {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char confirm_password[PASSWORD_LENGTH + 1];

    printf("Enter your current email: ");
    fgets(old_email, MAX_EMAIL_LEN, stdin);
    old_email[strcspn(old_email, "\n")] = '\0';

    if (strcmp(user->email, old_email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    printf("Enter your password: ");
    fgets(confirm_password, PASSWORD_LENGTH + 1, stdin);
    confirm_password[strcspn(confirm_password, "\n")] = '\0';

    if (strcmp(user->password, confirm_password) != 0) {
        printf("Password is incorrect.\n");
        return;
    }

    printf("Enter new email: ");
    fgets(new_email, MAX_EMAIL_LEN, stdin);
    new_email[strcspn(new_email, "\n")] = '\0';

    if (strcmp(user->email, new_email) == 0) {
        printf("New email must be different from the current email.\n");
        return;
    }

    strcpy(user->email, new_email);
    printf("Email changed successfully!\n");
}

int main() {
    User user = {"john_doe", "old.email@example.com", "password123"};

    char entered_email[MAX_EMAIL_LEN];
    char entered_password[PASSWORD_LENGTH + 1];

    printf("Enter your email: ");
    fgets(entered_email, MAX_EMAIL_LEN, stdin);
    entered_email[strcspn(entered_email, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(entered_password, PASSWORD_LENGTH + 1, stdin);
    entered_password[strcspn(entered_password, "\n")] = '\0';

    if (authenticate_user(&user, entered_email, entered_password)) {
        change_email(&user);
    } else {
        printf("Authentication failed.\n");
    }

    return 0;
}