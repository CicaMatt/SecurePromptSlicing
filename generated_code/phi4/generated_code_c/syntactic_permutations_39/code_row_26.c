#include <stdio.h>
#include <string.h>

// Function prototypes
void login();
int authenticate(const char *username, const char *password);
void session();

int main() {
    login();
    return 0;
}

void login() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    // Remove newline character
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    // Remove newline character
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }

    if (authenticate(username, password)) {
        session();
    } else {
        printf("Incorrect username or password.\n");
    }
}

int authenticate(const char *username, const char *password) {
    // Hardcoded credentials for demonstration
    return strcmp(username, "admin") == 0 && strcmp(password, "password123") == 0;
}

void session() {
    printf("Welcome to the session page!\n");
}