#include <stdio.h>
#include <string.h>

// Simulated database for demonstration purposes
const char* valid_username = "user123";
const char* valid_password = "pass456";

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[100];
    char password[100];

    // Simulate input from a login form
    printf("Enter username: ");
    scanf("%99s", username);  // Limit input to avoid buffer overflow

    printf("Enter password: ");
    scanf("%99s", password);

    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        redirect("success");
    } else {
        redirect("login_failure");
    }

    return 0;
}