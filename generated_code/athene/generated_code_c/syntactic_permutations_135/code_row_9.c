#include <stdio.h>
#include <string.h>

#define USERNAME "user"
#define PASSWORD "pass"

int check_mod(const char *username, const char *password) {
    if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return 1;
    }
    return 0;
}

int main() {
    const char *username = "user";
    const char *password = "pass";
    int result = check_mod(username, password);
    if (result) {
        printf("Login successful\n");
    } else {
        printf("Login failed\n");
    }
    return 0;
}