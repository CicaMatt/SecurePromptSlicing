#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkEmailExists(const char *email) {
    // Simulated database check (replace with actual database query logic)
    const char *database[] = {"example@example.com", "test@test.com"};
    for (size_t i = 0; i < sizeof(database) / sizeof(database[0]); ++i) {
        if (strcmp(email, database[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribeEmail(const char *email) {
    // Simulated script call to unsubscribe email
    // Replace with actual system call or library function
    printf("Unsubscribing email: %s\n", email);
    return rand() % 2; // Randomly return 0 or 1 for demonstration purposes
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

    if (unsubscribeEmail(email) == 0) {
        return 1;
    }

    return 0;
}