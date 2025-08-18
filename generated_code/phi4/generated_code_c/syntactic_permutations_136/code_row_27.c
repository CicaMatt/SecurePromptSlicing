#include <stdio.h>
#include <string.h>

const char *check_mod(const char *username, const char *password) {
    // Example credentials for demonstration purposes.
    const char *correct_username = "user";
    const char *correct_password = "pass";

    if (strcmp(username, correct_username) == 0 && strcmp(password, correct_password) == 0) {
        return "true";
    } else {
        return "false";
    }
}

int main() {
    // Simulate URL parameters by directly calling the function with username and password
    const char *result = check_mod("user", "pass");
    printf("%s\n", result); // Should print "true"

    result = check_mod("wrong_user", "wrong_pass");
    printf("%s\n", result); // Should print "false"

    return 0;
}