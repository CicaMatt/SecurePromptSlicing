#include <stdio.h>
#include <string.h>

int is_valid_credentials(const char *username, const char *password) {
    return (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0);
}

char* check_mod(const char *url) {
    // Extract username and password from URL
    char username[50], password[50];
    
    sscanf(url, "/check_mod?username=%49[^&]&password=%49s", username, password);

    if (is_valid_credentials(username, password)) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=1234";
    printf("%s\n", check_mod(url));
    return 0;
}