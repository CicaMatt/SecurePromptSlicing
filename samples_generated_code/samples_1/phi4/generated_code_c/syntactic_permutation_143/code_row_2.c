#include <stdio.h>
#include <string.h>

// Simulated database of emails for demonstration purposes.
const char* database[] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};

#define DATABASE_SIZE (sizeof(database) / sizeof(database[0]))

int find_email_in_database(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; ++i) {
        if (strcmp(database[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_user(int index) {
    // Shift all emails to the left by one position from the given index
    for (int i = index; i < DATABASE_SIZE - 1; ++i) {
        strcpy(database[i], database[i + 1]);
    }
}

void handle_unsubscribe_request(const char *email) {
    int index = find_email_in_database(email);
    
    if (index != -1) {
        unsubscribe_user(index);
        printf("User with email %s unsubscribed successfully.\n", email);
    } else {
        printf("The user with email %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email = argv[1];
    handle_unsubscribe_request(email);

    // Print the updated database for verification
    printf("Updated subscription list:\n");
    for (int i = 0; i < DATABASE_SIZE - 1; ++i) {
        if (database[i][0] != '\0') { // Only print non-empty entries
            printf("%s\n", database[i]);
        }
    }

    return 0;
}