#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes.
typedef struct {
    char username[50];
    char password[50];
} User;

User database[] = {
    {"user1", "password123"},
    {"user2", "pass456"}
};

int check_credentials(const char *username, const char *password) {
    for (size_t i = 0; i < sizeof(database) / sizeof(User); ++i) {
        if (strcmp(database[i].username, username) == 0 &&
            strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void redirect(const char *location) {
    printf("Redirecting to %s\n", location);
}

int main() {
    char input_username[50];
    char input_password[50];

    // Simulate user input
    printf("Enter username: ");
    scanf("%49s", input_username);

    printf("Enter password: ");
    scanf("%49s", input_password);

    if (check_credentials(input_username, input_password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    // Error handling simulation
    int error_occurred = 0; // Set to 1 if an error occurs

    if (error_occurred) {
        redirect("internal_server_error");
    }

    return 0;
}