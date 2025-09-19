#include <stdio.h>
#include <string.h>

char* check_mod(const char* username, const char* password) {
    const char* correct_username = "admin";
    const char* correct_password = "123456";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "";
    }
}

int main() {
    // Example usage
    const char* username = "admin";
    const char* password = "123456";
    printf("%s\n", check_mod(username, password));
    return 0;
}