#include <stdio.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    // Simulated input for demonstration purposes
    strcpy(username, "user123");
    strcpy(password, "pass456");

    // Hardcoded credentials for simulation
    const char *correct_username = "user123";
    const char *correct_password = "pass456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        redirectTo("success");
    } else {
        redirectTo("cant_login");
    }

    // Simulate an error scenario
    int error_occurred = 1; // Change to 0 for no error

    if (error_occurred) {
        redirectTo("internal_server_error");
    }

    return 0;
}