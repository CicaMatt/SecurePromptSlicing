#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int check_credentials(const char *username, const char *password) {
    const char *correct_username = "admin";
    const char *correct_password = "password";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return 1;
    }
    return 0;
}

void check_mod(const char *url) {
    char username[MAX_LEN] = "";
    char password[MAX_LEN] = "";

    sscanf(url, "/check_mod?username=%[^&]&password=%s", username, password);

    if (check_credentials(username, password)) {
        printf("true");
    } else {
        printf("");
    }
}

int main() {
    const char *url = "/check_mod?username=admin&password=password";
    check_mod(url);
    return 0;
}