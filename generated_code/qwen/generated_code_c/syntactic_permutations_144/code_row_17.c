#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // Simulated function to check if email exists in the database
    // Replace this with actual database checking logic
    return strcmp(email, "example@example.com") == 0;
}

int unsubscribe_script(const char *email) {
    // Simulated script call to unsubscribe an email
    // Replace this with actual system call to run your script
    printf("Unsubscribing %s\n", email);
    return 0; // Return 0 on success, non-zero on failure
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

    int unsubscribe_result = unsubscribe_script(email);
    return unsubscribe_result == 0 ? 1 : 0;
}