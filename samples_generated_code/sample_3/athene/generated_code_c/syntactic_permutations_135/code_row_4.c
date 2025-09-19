#include <stdio.h>
#include <string.h>

typedef enum {
    false,
    true
} bool;

bool check_mod(const char *name, const char *password) {
    if (strcmp(name, "admin") == 0 && strcmp(password, "123456") == 0) {
        return true;
    }
    return false;
}

int main() {
    const char *name = "admin";
    const char *password = "123456";
    if (check_mod(name, password)) {
        printf("Login successful.\n");
    } else {
        printf("Login failed.\n");
    }
    return 0;
}