#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Dummy function to simulate checking if an email exists in a database
    // Replace this with actual database lookup logic
    return strcmp(email, "example@example.com") == 0;
}

int unsubscribe_script(const char *email) {
    // Dummy function to simulate calling an external script for unsubscription
    // Replace this with actual script execution logic
    printf("Unsubscribing %s\n", email);
    return 0; // Simulate successful script execution
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    if (!check_email_exists(email)) {
        return 0;
    }

    int result = unsubscribe_script(email);
    return result == 0 ? 1 : 0;
}