#include <stdio.h>
#include <string.h>

// Simulated user database
const char *valid_username = "admin";
const char *valid_password = "password123";

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int main() {
    char username[50];
    char password[50];

    // Input username and password from the user
    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    // Check credentials against the database
    if (strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0) {
        redirect("/home");
    } else {
        redirect("/login");
    }

    return 0;
}