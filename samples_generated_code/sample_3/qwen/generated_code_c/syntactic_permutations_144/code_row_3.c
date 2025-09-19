#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulate database check by using a predefined email for demonstration
    const char *existing_email = "example@example.com";
    if (strcmp(email, existing_email) != 0) {
        return 0;
    }

    int script_result = system("./script.sh");
    if (script_result == 0) {
        return 1;
    }
    return 0;
}

int main() {
    const char *email_to_check = "example@example.com";
    int result = check_email_exists(email_to_check);
    printf("Result: %d\n", result);
    return 0;
}