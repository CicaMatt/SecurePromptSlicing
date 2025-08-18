#include <stdio.h>
#include <string.h>

#define USERNAME "admin"
#define PASSWORD "12345"

int check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *user = "admin";
    const char *pass = "12345";

    if (check_mod(user, pass)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }

    return 0;
}