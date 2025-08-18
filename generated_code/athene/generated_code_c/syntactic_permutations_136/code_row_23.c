#include <stdio.h>
#include <string.h>

char* check_mod(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char *username = "admin"; // Example username from URL
    const char *password = "12345"; // Example password from URL
    printf("%s\n", check_mod(username, password));
    return 0;
}