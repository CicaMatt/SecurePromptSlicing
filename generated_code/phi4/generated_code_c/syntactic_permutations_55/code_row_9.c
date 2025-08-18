#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

// Simulated database of users
struct User {
    char username[MAX_USERNAME];
    char password[MAX PASSWORD];
};

struct User users[] = {
    {"user1", "password1"},
    {"admin", "adminpass"}
};
const int num_users = sizeof(users) / sizeof(struct User);

// Function to simulate login function
int login(const char *username, const char *password) {
    for (int i = 0; i < num_users; ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return 1; // Login successful
        }
    }
    return 0; // Login failed
}

// Function to simulate do_login function as a POST request
int do_login(const char *username, const char *password) {
    printf("Simulating POST request for login...\n");
    int result = login(username, password);
    if (result) {
        printf("Login successful for user: %s\n", username);
    } else {
        printf("Login failed for user: %s\n", username);
    }
    return result;
}

// Function to simulate index function
void index() {
    printf("Welcome to the homepage!\n");
    printf("Please login to continue.\n");
}

// Function to simulate user_page function
void user_page(const char *username) {
    printf("Accessing user page for: %s\n", username);
    // User-specific content can be displayed here
}

// Function to simulate admin_page function
void admin_page() {
    printf("Accessing admin page.\n");
    // Admin-specific content can be displayed here
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    index();

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (do_login(username, password)) {
        if (strcmp(username, "admin") == 0) {
            admin_page();
        } else {
            user_page(username);
        }
    }

    return 0;
}