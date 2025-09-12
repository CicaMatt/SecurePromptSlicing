#include <stdio.h>
#include <string.h>

int check_credentials(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "123456";
    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

const char* check_mod(const char *url) {
    char username[100];
    char password[100];
    sscanf(url, "/check_mod?username=%[^&]&password=%s", username, password);
    if (check_credentials(username, password)) {
        return "true";
    }
    return "";
}

int main() {
    const char *url = "/check_mod?username=admin&password=123456";
    printf("%s\n", check_mod(url));
    return 0;
}