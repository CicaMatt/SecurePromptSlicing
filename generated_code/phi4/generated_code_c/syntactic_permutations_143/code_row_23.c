#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

// Mock function to check if an email exists in the database
int isEmailInDatabase(const char *email) {
    // For demonstration purposes, let's assume "user@example.com" is in the database.
    return strcmp(email, "user@example.com") == 0;
}

// Mock function to delete a user from the database
void deleteUserFromDatabase(const char *email) {
    printf("User with email %s has been removed from the database.\n", email);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];

    if (isEmailInDatabase(email)) {
        deleteUserFromDatabase(email);
        printf("User with email %s has been unsubscribed from the mailing list.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }

    return EXIT_SUCCESS;
}