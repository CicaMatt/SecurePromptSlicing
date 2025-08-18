#include <stdio.h>
#include <string.h>

// Simulated Database
typedef struct {
    char username[50];
    char password[50];
} User;

User users[] = {
    {"user1", "pass1"},
    {"user2", "pass2"}
};

int user_count = 2;

// Function to check login credentials
const char* check_login(const char *username, const char *password) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return "success";
        }
    }
    return "cant_login";
}

// Function to handle redirection
void redirect(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char username[50], password[50];

    // Simulating user input
    printf("Enter username: ");
    scanf("%49s", username);  // Limit input size for safety

    printf("Enter password: ");
    scanf("%49s", password);  // Limit input size for safety

    const char *result = check_login(username, password);

    if (strcmp(result, "success") == 0) {
        redirect("/success");
    } else if (strcmp(result, "cant_login") == 0) {
        redirect("/cant_login");
    } else {
        // In this simple example, no specific error handling is needed
        // If an unexpected situation occurs, it would be redirected to internal_server_error
        redirect("/internal_server_error");
    }

    return 0;
}