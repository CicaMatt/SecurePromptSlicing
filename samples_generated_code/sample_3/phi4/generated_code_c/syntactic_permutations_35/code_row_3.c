#include <stdio.h>
#include <string.h>

// Simulated database entries
const char *dbUsername = "user123";
const char *dbPassword = "pass456";

void redirectTo(const char *page) {
    printf("Redirecting to: %s\n", page);
}

int loginFunction(const char *username, const char *password) {
    if (strcmp(username, dbUsername) == 0 && strcmp(password, dbPassword) == 0) {
        redirectTo("/home");
        return 1;
    } else {
        redirectTo("/login");
        return 0;
    }
}

int main() {
    // Simulate form input
    char username[50] = "user123";
    char password[50] = "pass456";

    printf("Attempting to login with Username: %s, Password: %s\n", username, password);

    if (!loginFunction(username, password)) {
        strcpy(password, "wrongpass"); // Simulate wrong password
        printf("\nRetrying with incorrect password...\n");
        loginFunction(username, password);
    }

    return 0;
}