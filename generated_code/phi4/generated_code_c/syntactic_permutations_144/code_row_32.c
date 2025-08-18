#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to check if an email exists in the database.
int isEmailInDatabase(const char *email) {
    // For demonstration purposes, assume "test@example.com" is in the database.
    return strcmp(email, "test@example.com") == 0;
}

// Mock function to call a script that unsubscribes an email.
int unsubscribeEmailScript(const char *email) {
    // Simulate calling an external script and returning its status.
    // For demonstration purposes, assume the script is successful for any input.
    return system(NULL); // Replace with actual script call, e.g., `system("script.sh")`
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (!isEmailInDatabase(email)) {
        printf("0\n");
        return 0;
    }

    int unsubscribeResult = unsubscribeEmailScript(email);

    if (unsubscribeResult == 0) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}