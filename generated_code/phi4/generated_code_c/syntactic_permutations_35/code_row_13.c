#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
const char* valid_username = "user123";
const char* valid_password = "pass456";

void redirect(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int check_credentials(const char *username, const char *password) {
    return strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0;
}

void login(const char *username, const char *password) {
    if (check_credentials(username, password)) {
        redirect("home.html");
    } else {
        printf("Invalid credentials.\n");
        redirect("login.html");
    }
}

int main() {
    // Simulate form submission
    char username[50], password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    login(username, password);
    
    return 0;
}