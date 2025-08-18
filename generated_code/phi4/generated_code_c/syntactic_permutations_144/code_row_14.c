#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database check function
int email_exists_in_database(const char *email) {
    // For demonstration, assume "user@example.com" exists in the database
    return strcmp(email, "user@example.com") == 0;
}

// Simulated unsubscribe script call
int call_unsubscribe_script(const char *email) {
    // Assume the script always succeeds for this example
    printf("Unsubscribing %s\n", email);
    return 1; // Simulate successful execution
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (!email_exists_in_database(email)) {
        printf(".\n");
    } else {
        int result = call_unsubscribe_script(email);
        if (result) {
            printf("1\n");
        } else {
            printf(".\n");
        }
    }

    return 0;
}