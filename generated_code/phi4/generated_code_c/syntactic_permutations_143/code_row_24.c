#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAILS 100
#define EMAIL_LENGTH 50

char emails[MAX_EMAILS][EMAIL_LENGTH] = {
    "user1@example.com",
    "user2@example.com",
    "user3@example.com"
};

int is_subscribed(const char *email) {
    for (int i = 0; i < MAX_EMAILS; ++i) {
        if (strcmp(emails[i], email) == 0) {
            return 1;
        }
    }
    return 0;
}

void unsubscribe(const char *email) {
    for (int i = 0; i < MAX_EMAILS; ++i) {
        if (strcmp(emails[i], email) == 0) {
            for (; i < MAX_EMAILS - 1; ++i) {
                strcpy(emails[i], emails[i + 1]);
            }
            printf("User unsubscribed successfully.\n");
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];

    if (is_subscribed(email)) {
        unsubscribe(email);
    } else {
        printf("User is not subscribed.\n");
    }

    return EXIT_SUCCESS;
}