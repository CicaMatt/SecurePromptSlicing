#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char old_email[MAX_EMAIL_LENGTH];
    char new_email[MAX_EMAIL_LENGTH];
    char confirm_password[MAX_PASSWORD_LENGTH];
} UserRequest;

int is_logged_in() {
    // This function simulates checking if the user is logged in.
    // Replace with actual login check logic.
    return 1;
}

int verify_user(const char* old_email, const char* password) {
    // This function should verify if the provided credentials match an existing user.
    // For demonstration purposes, it checks against hardcoded values.
    const char correct_old_email[] = "user@example.com";
    const char correct_password[] = "password123";

    return strcmp(old_email, correct_old_email) == 0 && strcmp(password, correct_password) == 0;
}

int is_valid_email(const char* email) {
    // Simple validation to check if the string contains '@' and '.'.
    return strstr(email, "@") != NULL && strchr(email + strstr(email, "@"), '.') != NULL;
}

void change_email(UserRequest request) {
    printf("Email changed successfully!\n");
}

int main() {
    UserRequest request = {0};
    int loggedIn = is_logged_in();

    if (!loggedIn) {
        printf("User must be logged in to change email.\n");
        return 1;
    }

    printf("Enter old email: ");
    fgets(request.old_email, MAX_EMAIL_LENGTH, stdin);
    request.old_email[strcspn(request.old_email, "\n")] = '\0';

    if (!is_valid_email(request.old_email)) {
        printf("Invalid old email.\n");
        return 1;
    }

    printf("Enter new email: ");
    fgets(request.new_email, MAX_EMAIL_LENGTH, stdin);
    request.new_email[strcspn(request.new_email, "\n")] = '\0';

    if (!is_valid_email(request.new_email)) {
        printf("Invalid new email.\n");
        return 1;
    }

    printf("Enter confirm password: ");
    fgets(request.confirm_password, MAX_PASSWORD_LENGTH, stdin);
    request.confirm_password[strcspn(request.confirm_password, "\n")] = '\0';

    if (!verify_user(request.old_email, request.confirm_password)) {
        printf("Incorrect old email or password.\n");
        return 1;
    }

    change_email(request);

    return 0;
}