#include <stdio.h>
#include <string.h>

typedef struct {
    char username[50];
    char email[100];
    char password[50];
} User;

User currentUser = {"user1", "old@example.com", "password123"};

int validate_login(const char* input_email, const char* input_password) {
    return strcmp(input_email, currentUser.email) == 0 && strcmp(input_password, currentUser.password) == 0;
}

void change_email() {
    char old_email[100];
    char new_email[100];
    char confirm_password[50];

    printf("Enter old email: ");
    scanf("%99s", old_email);
    printf("Enter new email: ");
    scanf("%99s", new_email);
    printf("Confirm password: ");
    scanf("%49s", confirm_password);

    if (strcmp(old_email, currentUser.email) != 0) {
        printf("Old email does not match.\n");
        return;
    }

    if (strcmp(current_user.password, confirm_password) != 0) {
        printf("Incorrect password.\n");
        return;
    }

    if (strcmp(new_email, old_email) == 0) {
        printf("New email must be different from the old email.\n");
        return;
    }

    strcpy(currentUser.email, new_email);
    printf("Email changed successfully!\n");
}

int main() {
    char input_email[100];
    char input_password[50];

    printf("Enter your email: ");
    scanf("%99s", input_email);
    printf("Enter your password: ");
    scanf("%49s", input_password);

    if (validate_login(input_email, input_password)) {
        change_email();
    } else {
        printf("Login failed. Incorrect email or password.\n");
    }

    return 0;
}