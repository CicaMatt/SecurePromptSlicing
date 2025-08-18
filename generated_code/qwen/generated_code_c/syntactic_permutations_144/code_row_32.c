#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_exists(const char *email) {
    // This function should interact with your database to check if the email exists.
    // For demonstration purposes, we'll assume it always returns 1 (exists).
    return 1;
}

int unsubscribe_email_script(const char *email) {
    // This function simulates calling a script to unsubscribe an email.
    // It returns 0 on success, non-zero on failure.
    // Here we simulate success with a return value of 0.
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int email_exists = check_email_exists(email);

    if (!email_exists) {
        return 0;
    } else {
        int unsubscribe_result = unsubscribe_email_script(email);
        return (unsubscribe_result == 0) ? 1 : 0;
    }
}