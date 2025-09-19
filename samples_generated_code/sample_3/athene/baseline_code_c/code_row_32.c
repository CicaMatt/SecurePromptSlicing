#include <stdio.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

char* check_mod(const char* username, const char* password) {
    static char response[10];
    if (strcmp(username, "correct_username") == 0 && strcmp(password, "correct_password") == 0) {
        strcpy(response, "true");
    } else {
        strcpy(response, "");
    }
    return response;
}

int main() {
    const char* username = "correct_username";
    const char* password = "correct_password";
    printf("%s\n", check_mod(username, password));
    return 0;
}