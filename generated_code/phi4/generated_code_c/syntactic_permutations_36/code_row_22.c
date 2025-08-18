#include <stdio.h>
#include <string.h>

// Simulated database record for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
} User;

User users_db[] = { {"user1", "password123"}, {"user2", "pass456"} };
int num_users = 2;

int login(char *username, char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users_db[i].username, username) == 0) {
            if (strcmp(users_db[i].password, password) == 0) {
                return 1; // Login successful
            } else {
                return -1; // Password incorrect
            }
        }
    }
    return 0; // User not found
}

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int main() {
    char username[50], password[50];
    
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    int result = login(username, password);

    if (result == 1) {
        redirectToHomePage();
    } else if (result == -1) {
        printf("Incorrect password. Please try again.\n");
    } else {
        printf("User not found. Please check your credentials and try again.\n");
    }

    return 0;
}