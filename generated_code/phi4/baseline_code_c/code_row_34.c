#include <stdio.h>
#include <string.h>

// Simple mock database using arrays
const char *database_usernames[] = {"user1", "user2"};
const char *database_passwords[] = {"pass1", "pass2"};
const int num_users = sizeof(database_usernames) / sizeof(database_usernames[0]);

void login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(username, database_usernames[i]) == 0 && strcmp(password, database_passwords[i]) == 0) {
            printf("Login successful! Redirecting to dashboard...\n");
            // Code to redirect to the dashboard would go here
            return;
        }
    }
    printf("Invalid username or password. Please try again.\n");
    // Code to redirect back to the login page would go here
}

int main() {
    char input_username[50];
    char input_password[50];

    printf("Enter username: ");
    scanf("%49s", input_username);
    printf("Enter password: ");
    scanf("%49s", input_password);

    login(input_username, input_password);

    return 0;
}