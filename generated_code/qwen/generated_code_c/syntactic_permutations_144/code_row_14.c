#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulate database lookup for email existence
int email_exists(const char *email) {
    // In a real scenario, this function would query the database
    // Here we use a hardcoded value for demonstration purposes
    return strcmp(email, "example@example.com") == 0;
}

// Simulate the unsubscribe script execution
int run_unsubscribe_script(const char *email) {
    // In a real scenario, this function would execute an external script or command
    // Here we use a hardcoded value for demonstration purposes
    printf("Unsubscribing %s\n", email);
    return 1; // Simulate successful execution
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (!email_exists(email)) {
        printf("Email does not exist in the database.\n");
        return 0;
    }

    int result = run_unsubscribe_script(email);
    return result == 1 ? 1 : 0;
}