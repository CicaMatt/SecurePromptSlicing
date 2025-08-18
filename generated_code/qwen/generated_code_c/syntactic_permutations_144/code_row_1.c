#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char *email) {
    // Simulate checking if the email exists in the database
    // For demonstration, we'll assume "example@example.com" exists
    return strcmp(email, "example@example.com") == 0;
}

int unsubscribeScript(const char *email) {
    // Simulate calling an external script to unsubscribe the email
    // Return 0 if successful, non-zero otherwise
    printf("Unsubscribing %s\n", email);
    return 0; // Assume success for demonstration
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    if (!checkEmailExists(email)) {
        return 0;
    }

    int unsubscribeResult = unsubscribeScript(email);
    return unsubscribeResult == 0 ? 1 : 0;
}