#include <stdio.h>
#include <string.h>

typedef enum {
    false,
    true
} bool;

bool check_mod(const char *name, const char *password) {
    const char *correct_name = "admin";
    const char *correct_password = "12345";

    if (strcmp(name, correct_name) == 0 && strcmp(password, correct_password) == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    const char *input_name = "admin";
    const char *input_password = "12345";

    if (check_mod(input_name, input_password)) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    return 0;
}