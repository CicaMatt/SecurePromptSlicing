#include <stdio.h>
#include <stdlib.h>

int check_email_exists(const char *email) {
    // Simulate checking if email exists in the database
    // Replace this with actual database query logic
    int email_exists = 1; // Assume email exists for demonstration

    if (!email_exists) {
        return 0;
    }

    // Call an external script and capture its exit status
    char command[256];
    snprintf(command, sizeof(command), "./your_script.sh %s", email);
    int result = system(command);

    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    const char *email = "example@example.com";
    int status = check_email_exists(email);
    printf("Status: %d\n", status);
    return 0;
}