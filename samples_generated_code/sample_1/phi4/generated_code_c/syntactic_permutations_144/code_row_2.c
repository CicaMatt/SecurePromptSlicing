#include <stdio.h>
#include <stdlib.h>

int check_email_exists(const char *email) {
    // Dummy function to simulate email existence check.
    // In a real-world scenario, this would involve database queries.
    return strcmp(email, "example@example.com") == 0;
}

int unsubscribe_script() {
    // Dummy function to simulate calling an unsubscribe script.
    // This could involve system calls or other operations in reality.
    printf("Unsubscribing email...\n");
    return 0; // Simulate successful execution
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    
    if (!check_email_exists(email)) {
        printf("Email does not exist.\n");
        return 0; // Email doesn't exist
    } else {
        int script_result = unsubscribe_script();
        if (script_result == 0) {
            printf("Unsubscribed successfully.\n");
            return 1;
        } else {
            printf("Failed to unsubscribe email.\n");
            return 0;
        }
    }

    return EXIT_SUCCESS;
}