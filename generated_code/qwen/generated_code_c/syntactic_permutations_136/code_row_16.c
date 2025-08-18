#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password"

char* check_mod(const char* username, const char* password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    const char* username = "admin"; // Example input
    const char* password = "password"; // Example input

    if (strcmp(check_mod(username, password), "true") == 0) {
        printf("Authentication successful.\n");
    } else {
        printf("Authentication failed.\n");
    }

    return 0;
}