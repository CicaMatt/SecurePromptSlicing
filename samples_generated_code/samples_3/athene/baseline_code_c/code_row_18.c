#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "password123"

char* check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return "true";
    }
    return "";
}

int main() {
    // Example usage
    const char *username = "admin";
    const char *password = "password123";
    printf("%s\n", check_mod(username, password));
    return 0;
}