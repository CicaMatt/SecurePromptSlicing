#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

char* check_mod(const char* url_username, const char* url_password) {
    if (strcmp(url_username, USERNAME) == 0 && strcmp(url_password, PASSWORD) == 0) {
        return "true";
    }
    return "";
}

int main() {
    const char* username = "admin"; // Example username from URL
    const char* password = "12345"; // Example password from URL
    printf("%s\n", check_mod(username, password));
    return 0;
}