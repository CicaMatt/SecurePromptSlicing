#include <stdio.h>
#include <string.h>

// Simulate a database with predefined user credentials
const char* correct_username = "user123";
const char* correct_password = "password456";

void redirect(const char* page) {
    printf("Redirecting to: %s\n", page);
}

int main() {
    char username[100];
    char password[100];

    // Simulate input for username and password
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[--len] = '\0';
    }

    // Check credentials
    int login_successful = strcmp(username, correct_username) == 0 &&
                           strcmp(password, correct_password) == 0;

    if (login_successful) {
        redirect("home_page");
    } else {
        redirect("cant_login");
    }

    return 0;
}