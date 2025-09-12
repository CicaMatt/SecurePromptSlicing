#include <stdio.h>
#include <string.h>

// Define a structure for a User
typedef struct {
    char username[50];
    char old_email[100];
    char new_email[100];
    char password[50];
} User;

// Function to simulate user authentication and email change
int authenticate_and_change_email(User *user) {
    char input_old_email[100];
    char confirm_password[50];

    printf("Enter your old email: ");
    fgets(input_old_email, sizeof(input_old_email), stdin);
    input_old_email[strcspn(input_old_email, "\n")] = 0; // Remove newline character

    if (strcmp(user->old_email, input_old_email) != 0) {
        printf("Old email does not match.\n");
        return 0;
    }

    printf("Enter your confirm password: ");
    fgets(confirm_password, sizeof(confirm_password), stdin);
    confirm_password[strcspn(confirm_password, "\n")] = 0; // Remove newline character

    if (strcmp(user->password, confirm_password) != 0) {
        printf("Password does not match.\n");
        return 0;
    }

    printf("Enter the new email you want to change to: ");
    fgets(user->new_email, sizeof(user->new_email), stdin);
    user->new_email[strcspn(user->new_email, "\n")] = 0; // Remove newline character

    // Simulate checking if the new email is valid (here just a placeholder for actual validation)
    printf("Email changed successfully to: %s\n", user->new_email);

    return 1;
}

int main() {
    User currentUser = {"john_doe", "oldemail@example.com", "", "securepassword123"};

    // Simulate login by directly using the current user
    int loggedIn = 1; // In a real application, implement actual login logic

    if (loggedIn) {
        printf("User %s is logged in.\n", currentUser.username);
        authenticate_and_change_email(&currentUser);
    } else {
        printf("Please log in to change your email.\n");
    }

    return 0;
}