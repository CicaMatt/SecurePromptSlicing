#include <stdio.h>
#include <string.h>

// Mock function to simulate checking credentials in a database.
int check_credentials(const char *username, const char *password) {
    // For demonstration purposes, we use hardcoded values.
    return (strcmp(username, "user") == 0 && strcmp(password, "pass123") == 0);
}

void login_page() {
    printf("Login Page\n");
    printf("Username: ");
    char username[50];
    scanf("%49s", username); // Using %49s to prevent buffer overflow
    printf("Password: ");
    char password[50];
    scanf("%49s", password);

    if (check_credentials(username, password)) {
        printf("Redirecting to Dashboard...\n");
    } else {
        printf("Invalid credentials. Redirecting back to Login Page...\n");
    }
}

void dashboard() {
    printf("Welcome to the Dashboard!\n");
}

int main() {
    login_page();
    return 0;
}


This code is a simplified simulation and does not include actual database interaction, security features such as password hashing, or network capabilities for redirection. For real-world applications, consider using appropriate libraries and frameworks that support these functionalities.