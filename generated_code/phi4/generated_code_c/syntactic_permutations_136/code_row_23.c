#include <stdio.h>
#include <string.h>

const char* check_mod(const char *username, const char *password) {
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        return "true";
    }
    return "";
}

int main() {
    // Simulate a call to the function with URL parameters
    const char* url_username = "admin";
    const char* url_password = "1234";

    printf("%s\n", check_mod(url_username, url_password));
    
    return 0;
}