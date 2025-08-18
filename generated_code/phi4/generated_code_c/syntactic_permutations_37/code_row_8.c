#include <stdio.h>
#include <string.h>

// Mock database for demonstration purposes
const char* valid_username = "user123";
const char* valid_password = "password";

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int check_credentials(const char* username, const char* password) {
    return strcmp(username, valid_username) == 0 && strcmp(password, valid_password) == 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character from input
    size_t len = strlen(username);
    if (len > 0 && username[len-1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character from input
    len = strlen(password);
    if (len > 0 && password[len-1] == '\n') {
        password[--len] = '\0';
    }

    if (check_credentials(username, password)) {
        redirect("success");
    } else {
        redirect("cant_login");
    }

    return 0;
}