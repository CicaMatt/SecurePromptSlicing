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
    const char *name = "admin";
    const char *password = "12345";

    bool result = check_mod(name, password);
    printf("%s\n", result ? "true" : "false");

    return 0;
}