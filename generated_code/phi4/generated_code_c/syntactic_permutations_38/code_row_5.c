#include <stdio.h>
#include <string.h>

// Simulated database for demonstration purposes
const char *database_username = "user123";
const char *database_password = "pass456";

void redirectTo(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", password);

    if (strcmp(username, database_username) == 0 && strcmp(password, database_password) == 0) {
        redirectTo("/dashboard");
    } else {
        redirectTo("/login");
    }

    return 0;
}