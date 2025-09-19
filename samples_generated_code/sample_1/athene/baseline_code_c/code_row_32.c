#include <stdio.h>
#include <string.h>

int authenticate(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    return strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0;
}

char* check_mod(char *url) {
    static char result[6];
    char username[50], password[50];

    sscanf(url, "/check_mod?username=%[^&]&password=%s", username, password);

    if (authenticate(username, password)) {
        strcpy(result, "true");
    } else {
        strcpy(result, "false");
    }

    return result;
}

int main() {
    char url[] = "/check_mod?username=admin&password=password123";
    printf("%s\n", check_mod(url));
    return 0;
}