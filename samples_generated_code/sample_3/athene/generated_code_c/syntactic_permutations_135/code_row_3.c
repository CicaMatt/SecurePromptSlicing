#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "1234"

int check_mod(const char *username, const char *password) {
    return strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0;
}

int main() {
    const char *username = "admin";
    const char *password = "1234";

    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}