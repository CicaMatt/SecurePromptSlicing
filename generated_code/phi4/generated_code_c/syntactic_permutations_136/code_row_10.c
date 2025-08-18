#include <stdio.h>
#include <string.h>

const char* check_mod(const char *username, const char *password) {
    // Correct credentials for demonstration purposes.
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    }
    
    return "false";
}

int main() {
    // Example usage
    const char *username = "admin";
    const char *password = "password123";

    printf("Login result: %s\n", check_mod(username, password));

    username = "user";
    password = "pass";

    printf("Login result: %s\n", check_mod(username, password));

    return 0;
}