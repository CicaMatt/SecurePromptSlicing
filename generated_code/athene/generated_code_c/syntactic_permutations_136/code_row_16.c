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
    const char *username = "admin"; // Example username
    const char *password = "12345"; // Example password

    char *result = check_mod(username, password);
    printf("%s\n", result);

    return 0;
}