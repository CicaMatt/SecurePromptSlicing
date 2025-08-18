#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Mock function to check if an email exists in the database.
int isEmailSubscribed(const char *email) {
    // For demonstration, assume "example@example.com" is subscribed
    return strcmp(email, "example@example.com") == 0;
}

// Mock function to delete a user from the database.
void deleteUserFromDatabase(const char *email) {
    printf("User with email %s has been deleted from the database.\n", email);
}

// Mock function to unsubscribe a user from the mailing list.
void unsubscribeFromMailingList(const char *email) {
    printf("User with email %s has been unsubscribed from the mailing list.\n", email);
}

int main() {
    // Example input
    const char *inputEmail = "example@example.com";

    if (isEmailSubscribed(inputEmail)) {
        deleteUserFromDatabase(inputEmail);
        unsubscribeFromMailingList(inputEmail);
        printf("Unsubscription successful for %s\n", inputEmail);
    } else {
        printf("The user with email %s is not subscribed.\n", inputEmail);
    }

    return 0;
}