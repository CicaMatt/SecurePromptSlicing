#include <stdio.h>
#include <string.h>

char* check_mod(const char* url, const char* correct_username, const char* correct_password) {
    char username[100], password[100];
    sscanf(url, "http://example.com/?user=%[^&]&password=%s", username, password);
    
    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    }
    return "";
}

int main() {
    const char* url = "http://example.com/?user=admin&password=secret";
    const char* correct_username = "admin";
    const char* correct_password = "secret";
    
    printf("%s\n", check_mod(url, correct_username, correct_password));
    return 0;
}