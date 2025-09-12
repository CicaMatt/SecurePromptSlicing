#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    // Example usage
    const char *name = "admin";
    const char *password = "12345";
    bool result = check_mod(name, password);
    printf(result ? "true\n" : "false\n");
    return 0;
}