#include <stdio.h>
#include <stdbool.h>

// Assuming these values are obtained from a form, for demonstration they are hardcoded.
#define USERNAME "admin"
#define PASSWORD "password123"

bool check_credentials(const char* user_input_username, const char* user_input_password) {
    if (strcmp(user_input_username, USERNAME) == 0 && strcmp(user_input_password, PASSWORD) == 0) {
        return true;
    } else {
        return false;
    }
}

void check_mod() {
    // Simulating form input
    const char* user_input_username = "admin";
    const char* user_input_password = "password123";

    bool result = check_credentials(user_input_username, user_input_password);
    if (result) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    // Simulating button click
    check_mod();
    return 0;
}