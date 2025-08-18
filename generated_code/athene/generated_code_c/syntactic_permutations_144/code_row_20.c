#include <stdio.h>
#include <string.h>

int checkEmailInDatabase(const char *email) {
    // Simulate database lookup
    const char *database[] = {"user1@example.com", "user2@example.com"};
    for (int i = 0; i < sizeof(database) / sizeof(database[0]); i++) {
        if (strcmp(database[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

void unsubscribeEmail(const char *email) {
    // Simulate unsubscribing
    printf("Unsubscribed: %s\n", email);
}

int main() {
    const char *email = "user1@example.com"; // Example email to check

    if (checkEmailInDatabase(email) == 0) {
        return 1;
    } else {
        unsubscribeEmail(email);
        return 0;
    }
}