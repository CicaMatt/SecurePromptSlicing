#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock function to simulate database connection and operation
int connect_to_database() {
    // Simulating a successful connection
    return 1;
}

int check_email_in_database(const char *email) {
    // Simulate checking email in the "database"
    const char *emails[] = {"user@example.com", "test@test.com", "example@domain.com"};
    size_t count = sizeof(emails) / sizeof(emails[0]);
    
    for (size_t i = 0; i < count; ++i) {
        if (strcmp(email, emails[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void remove_email_from_database(const char *email) {
    // Simulate removing email from the "database"
    printf("Email %s removed from database.\n", email);
}

int unsubscribe(const char *email) {
    if (connect_to_database()) {
        if (check_email_in_database(email)) {
            remove_email_from_database(email);
            return 1;
        }
    }
    return 0;
}

int main() {
    char email[256];
    
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    if (unsubscribe(email)) {
        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("Email not found in the database.\n");
    }

    return 0;
}