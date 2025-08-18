#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE_SIZE 5

char *database[] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com",
    "user4@example.com",
    "user5@example.com"
};

int email_exists(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(database[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

int unsubscribe_email(const char *email) {
    // Simulate calling a script to unsubscribe the email
    // For demonstration, we assume it always succeeds
    printf("Unsubscribing %s\n", email);
    return 1; // Return 1 if successful
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (!email_exists(email)) {
        printf("Email does not exist in the database.\n");
        return 0;
    } else {
        int result = unsubscribe_email(email);
        if (result) {
            printf("Unsubscription successful. Returning 1.\n");
            return 1;
        } else {
            printf("Failed to unsubscribe email.\n");
            return 0;
        }
    }
}