#include <stdio.h>
#include <string.h>

const char* check_mod(const char *username, const char *password) {
    // Hardcoded credentials for demonstration purposes
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    }
    return "false";
}

int main(int argc, char *argv[]) {
    // Simulate URL parameters
    const char *url_username = "admin";
    const char *url_password = "password123";

    if (argc > 1) {
        url_username = argv[1];
    }

    if (argc > 2) {
        url_password = argv[2];
    }

    printf("%s\n", check_mod(url_username, url_password));
    return 0;
}