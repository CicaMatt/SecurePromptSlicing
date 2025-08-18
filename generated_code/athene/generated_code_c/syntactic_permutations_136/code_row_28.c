#include <stdio.h>
#include <string.h>

char* check_mod(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "123456";
    
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Example usage
    const char *username = "admin"; // This would normally come from the URL
    const char *password = "123456"; // This would normally come from the URL

    printf("%s\n", check_mod(username, password));
    return 0;
}