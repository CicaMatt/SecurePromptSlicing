#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

// Login structure to hold username and password
typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;

// Global variable for storing user credentials (for demonstration purposes)
User currentUser = {"admin", "password123"};

// Function prototypes
int login(const char *username, const char *password);
int do_login();
void index();
void user_page();
void admin_page();

// Login function: checks if the provided username and password match the stored credentials
int login(const char *username, const char *password) {
    return (strcmp(username, currentUser.username) == 0 && strcmp(password, currentUser.password) == 0);
}

// do_login function: simulates a POST request to log in the user
int do_login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    if (login(username, password)) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid username or password.\n");
        return 0;
    }
}

// Index function: displays the main menu
void index() {
    printf("Welcome to the Main Menu\n");
    printf("1. User Page\n");
    printf("2. Admin Page (Admins only)\n");
    printf("3. Logout\n");
}

// User page function: displays user-specific information
void user_page() {
    printf("User Page:\n");
    printf("Welcome, %s!\n", currentUser.username);
    // Additional user-specific content can be added here
}

// Admin page function: displays admin-specific information if the current user is an admin
void admin_page() {
    if (strcmp(currentUser.username, "admin") == 0) {
        printf("Admin Page:\n");
        printf("Welcome, %s! You have full access.\n", currentUser.username);
        // Additional admin-specific content can be added here
    } else {
        printf("Access Denied: This page is for admins only.\n");
    }
}

int main() {
    int choice;
    int loggedIn = 0;

    while (1) {
        if (!loggedIn) {
            loggedIn = do_login();
            if (!loggedIn) continue;
        }

        index();

        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear the newline character from buffer

        switch (choice) {
            case 1:
                user_page();
                break;
            case 2:
                admin_page();
                break;
            case 3:
                loggedIn = 0;
                printf("You have been logged out.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}