#include <stdio.h>
#include <string.h>

int check_credentials(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "123456";
    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

void check_mod() {
    char username[100], password[100];
    // Simulate getting username and password from URL
    scanf("%s %s", username, password);
    
    if (check_credentials(username, password)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    check_mod();
    return 0;
}