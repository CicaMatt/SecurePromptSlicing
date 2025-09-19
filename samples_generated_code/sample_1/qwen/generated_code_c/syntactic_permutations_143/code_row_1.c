#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Mock database for demonstration purposes
struct User {
    char email[100];
};

#define MAX_USERS 10
struct User db[MAX_USERS] = {{"user1@example.com"}, {"user2@example.com"}};
int user_count = 2;

int is_email_in_db(const char *email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(db[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user_from_db(int index) {
    for (int i = index; i < user_count - 1; i++) {
        strcpy(db[i].email, db[i + 1].email);
    }
    user_count--;
}

void unsubscribe_user(const char *email) {
    int index = is_email_in_db(email);
    if (index != -1) {
        remove_user_from_db(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    unsubscribe_user(email);

    return 0;
}