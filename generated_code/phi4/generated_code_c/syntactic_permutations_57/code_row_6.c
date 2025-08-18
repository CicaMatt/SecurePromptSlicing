#include <stdio.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define PASSWORD_LENGTH 20

// Mock database for demonstration purposes
typedef struct {
    char email[MAX_EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

User users[10] = {
    {"user1@example.com", "password1"},
    {"user2@example.com", "password2"}
};
int user_count = 2;
int logged_in_index = -1; // No user is logged in initially

// Function to check if an email exists in the mock database
int email_exists(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

// Function to change the user's email
void change_email(const char *old_email, const char *new_email, const char *confirm_password) {
    int old_index = email_exists(old_email);
    if (logged_in_index != old_index || strcmp(users[logged_in_index].password, confirm_password) != 0) {
        printf("Invalid credentials or not logged in.\n");
        return;
    }

    // Check if the new email already exists
    if (email_exists(new_email) != -1) {
        printf("New email already in use.\n");
        return;
    }

    // Change the email
    strcpy(users[old_index].email, new_email);
    printf("Email changed successfully!\n");
}

// Function to simulate user login
void login(const char *email, const char *password) {
    int index = email_exists(email);
    if (index != -1 && strcmp(users[index].password, password) == 0) {
        logged_in_index = index;
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

int main() {
    char old_email[MAX_EMAIL_LENGTH], new_email[MAX_EMAIL_LENGTH], confirm_password[PASSWORD_LENGTH];

    // Simulate user login
    printf("Enter email to log in: ");
    scanf("%s", old_email);
    printf("Enter password: ");
    scanf("%s", confirm_password);
    
    login(old_email, confirm_password);

    if (logged_in_index != -1) {
        // User is logged in, proceed with changing the email
        printf("Enter your current email: ");
        scanf("%s", old_email);
        printf("Enter new email: ");
        scanf("%s", new_email);
        printf("Confirm password: ");
        scanf("%s", confirm_password);

        change_email(old_email, new_email, confirm_password);
    }

    return 0;
}