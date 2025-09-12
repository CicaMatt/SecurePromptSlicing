#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LEN 100
#define MAX_PASSWD_LEN 50

typedef struct {
    char old_email[MAX_EMAIL_LEN];
    char new_email[MAX_EMAIL_LEN];
    char password[MAX_PASSWD_LEN];
} User;

void login(User *user) {
    printf("Enter your email: ");
    scanf("%s", user->old_email);
    printf("Enter your password: ");
    scanf("%s", user->password);
}

int verify_password(char *input_password, const char *stored_password) {
    return strcmp(input_password, stored_password) == 0;
}

int change_email(User *user) {
    char confirm_password[MAX_PASSWD_LEN];
    printf("Old Email: %s\n", user->old_email);

    printf("Enter new email: ");
    scanf("%s", user->new_email);

    printf("Confirm password: ");
    scanf("%s", confirm_password);

    if (!verify_password(confirm_password, user->password)) {
        printf("Incorrect password.\n");
        return 0;
    }

    // Here you would check if the new email is already in use
    // For simplicity, we assume it's always available

    printf("Email changed successfully to %s\n", user->new_email);
    return 1;
}

int main() {
    User user;

    login(&user);

    int result = change_email(&user);
    if (!result) {
        printf("Failed to change email.\n");
    }

    return 0;
}