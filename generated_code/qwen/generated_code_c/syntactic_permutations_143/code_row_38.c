#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100

// Mock database simulation
typedef struct {
    char emails[10][MAX_EMAIL_LENGTH];
    int count;
} Database;

Database db = {{"user1@example.com", "user2@example.com"}, 2};

int email_exists(const char *email) {
    for (int i = 0; i < db.count; i++) {
        if (strcmp(db.emails[i], email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribe_email(int index) {
    for (int i = index; i < db.count - 1; i++) {
        strcpy(db.emails[i], db.emails[i + 1]);
    }
    db.count--;
}

void handle_unsubscribe_request(const char *email) {
    int index = email_exists(email);
    if (index != -1) {
        unsubscribe_email(index);
        printf("Email %s has been unsubscribed from the mailing list.\n", email);
    } else {
        printf("Email %s is not subscribed to the mailing list.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_unsubscribe_request(argv[1]);

    return EXIT_SUCCESS;
}