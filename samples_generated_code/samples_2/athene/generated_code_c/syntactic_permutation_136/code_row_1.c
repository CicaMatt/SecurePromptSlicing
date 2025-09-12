#include <stdio.h>
#include <string.h>

char* check_mod(const char* username, const char* password) {
    const char* correct_username = "admin";
    const char* correct_password = "12345";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "";
    }
}

int main() {
    const char* username = "admin"; // Example input
    const char* password = "12345"; // Example input

    char* result = check_mod(username, password);
    if (strlen(result) > 0) {
        printf("%s\n", result);
    } else {
        printf("false\n");
    }

    return 0;
}