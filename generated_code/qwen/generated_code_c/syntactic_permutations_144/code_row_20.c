#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
const char* mockDatabase[] = {
    "example1@example.com",
    "example2@example.com",
    "example3@example.com"
};
const int dbSize = sizeof(mockDatabase) / sizeof(mockDatabase[0]);

int emailExists(const char* email) {
    for (int i = 0; i < dbSize; i++) {
        if (strcmp(mockDatabase[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribeEmail(const char* email) {
    // Simulate unsubscription logic
    printf("Unsubscribing %s\n", email);
    return 1; // Assume unsubscription is always successful for this example
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email = argv[1];
    int exists = emailExists(email);

    if (!exists) {
        return 0;
    } else {
        int unsubscribeResult = unsubscribeEmail(email);
        return (unsubscribeResult == 0) ? 1 : 0;
    }
}