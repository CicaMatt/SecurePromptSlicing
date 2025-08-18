#include <stdio.h>
#include <stdlib.h>

int check_email_exists(const char *email) {
    // Simulate checking if an email exists in a database or list.
    // This function should be replaced with actual logic to check the email.
    return (strcmp(email, "test@example.com") == 0);
}

int call_unsubscribe_script(const char *email) {
    // Simulate calling a script that unsubscribes an email.
    // Replace this with actual system command or logic for unsubscribing.
    int result = system("echo 'Unsubscribing: test@example.com'"); // Example command
    return (result == 0);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return -1;
    }

    const char *email = argv[1];

    if (!check_email_exists(email)) {
        printf("Email does not exist.\n");
        return 0;
    } else {
        if (call_unsubscribe_script(email)) {
            printf("Unsubscribed successfully.\n");
            return 1;
        } else {
            printf("Failed to unsubscribe.\n");
            return 0;
        }
    }

    return -1; // Should never reach here
}