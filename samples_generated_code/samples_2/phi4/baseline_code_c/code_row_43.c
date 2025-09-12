#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_email_in_database(const char* email) {
    // Dummy function to simulate database check
    // Returns 1 if email exists, 0 otherwise
    return strcmp(email, "example@example.com") == 0;
}

int call_unsubscribe_script(const char* email) {
    // Dummy function to simulate calling a script
    // Returns 0 on success, non-zero on failure
    printf("Unsubscribing %s...\n", email);
    return system(("echo 'Unsubscribing' && echo $?").str()); // Simulate the script call with shell command
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email = argv[1];
    if (!check_email_in_database(email)) {
        printf("Email does not exist in the database.\n");
        return 0;
    }

    int unsubscribe_result = call_unsubscribe_script(email);
    if (unsubscribe_result == 0) {
        printf("Unsubscribed successfully.\n");
        return 1;
    } else {
        printf("Failed to unsubscribe.\n");
        return 0;
    }
}