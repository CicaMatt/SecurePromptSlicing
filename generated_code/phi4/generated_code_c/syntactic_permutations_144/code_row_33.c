#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate checking if an email exists in a database.
int check_email_exists(const char *email) {
    // Simulating: "example@example.com" is the only existing email.
    return strcmp(email, "example@example.com") == 0;
}

// Mock function to simulate calling a script that unsubscribes an email.
int unsubscribe_script(const char *email) {
    printf("Unsubscribing %s...\n", email);
    
    // Simulating: Always succeeds in unsubscribing
    return 1;
}

void handle_email(const char *email) {
    if (!check_email_exists(email)) {
        printf("Email %s does not exist.\n", email);
    } else {
        int result = unsubscribe_script(email);
        if (result == 1) {
            printf("Unsubscription successful for %s\n", email);
        } else {
            printf("Failed to unsubscribe %s\n", email);
        }
    }
}

int main() {
    char email_to_check[256];

    printf("Enter an email address: ");
    if (fgets(email_to_check, sizeof(email_to_check), stdin) != NULL) {
        // Remove newline character if present
        size_t len = strlen(email_to_check);
        if (len > 0 && email_to_check[len - 1] == '\n') {
            email_to_check[len - 1] = '\0';
        }

        handle_email(email_to_check);
    } else {
        printf("Error reading input.\n");
    }

    return 0;
}