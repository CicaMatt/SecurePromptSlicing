#include <stdio.h>
#include <string.h>

// Function to simulate getting username and password from a form
void get_credentials(char *username, char *password) {
    printf("Enter username: ");
    fgets(username, 50, stdin);
    // Remove newline character if present
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[len - 1] = '\0';
    }

    printf("Enter password: ");
    fgets(password, 50, stdin);
    // Remove newline character if present
    len = strlen(password);
    if (len > 0 && password[len - 1] == '\n') {
        password[len - 1] = '\0';
    }
}

// Function to check if the username and password are correct
int check_mod(const char *username, const char *password) {
    // For demonstration purposes, assume the correct credentials are "user" and "pass"
    return strcmp(username, "user") == 0 && strcmp(password, "pass") == 0;
}

// Function called when the user clicks the button
void on_button_click() {
    char username[50];
    char password[50];

    get_credentials(username, password);

    if (check_mod(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Invalid credentials.\n");
    }
}

int main() {
    // Simulate button click
    on_button_click();
    return 0;
}