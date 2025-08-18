#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Simulated function to mimic a button click event that calls check_mod
void simulateButtonClick();

bool check_mod(const char* username, const char* password) {
    // Hardcoded credentials for demonstration purposes
    const char* correct_username = "admin";
    const char* correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return true;
    } else {
        return false;
    }
}

void simulateButtonClick() {
    // Simulated username and password input from a form
    const char* username = "admin";
    const char* password = "password123";

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }
}

int main() {
    simulateButtonClick();
    return 0;
}