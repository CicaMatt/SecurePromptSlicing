#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

int check_mod(const char *user, const char *pass) {
    return strcmp(user, USERNAME) == 0 && strcmp(pass, PASSWORD) == 0;
}

int main() {
    const char *username = "admin";
    const char *password = "12345";
    if (check_mod(username, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }
    return 0;
}