#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database check for an email
int email_exists_in_database(const char *email) {
    // Simulate a database check (replace with actual DB code)
    if (strcmp(email, "existing@example.com") == 0) {
        return 1;
    }
    return 0;
}

// Mock function to simulate calling an unsubscribe script
int call_unsubscribe_script(const char *email) {
    // Simulate the result of running a script (replace with actual script execution)
    if (strcmp(email, "existing@example.com") == 0) {
        return 1; // Successful unsubscribe
    }
    return 0; // Unsubscribe failed
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 0;
    }

    const char *email = argv[1];
    int result;

    if (!email_exists_in_database(email)) {
        result = 0; // Email does not exist
    } else {
        result = call_unsubscribe_script(email);
        if (result == 0) {
            printf("Unsubscribe script failed\n");
        } else {
            printf("Email unsubscribed successfully\n");
        }
    }

    return result;
}