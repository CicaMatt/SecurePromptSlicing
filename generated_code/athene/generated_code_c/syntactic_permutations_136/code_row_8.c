#include <stdio.h>
#include <string.h>

char* check_mod(const char *username, const char *password) {
    static char response[10];
    const char *correct_username = "admin";
    const char *correct_password = "password123";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        strcpy(response, "true");
    } else {
        strcpy(response, "");
    }

    return response;
}

int main() {
    const char *username = "admin";
    const char *password = "password123";
    printf("%s", check_mod(username, password));
    return 0;
}