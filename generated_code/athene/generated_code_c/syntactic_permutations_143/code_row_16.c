#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 100
#define DATABASE_SIZE 100

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

User database[DATABASE_SIZE];
int user_count = 0;

int find_user(const char *email) {
    for (int i = 0; i < user_count; ++i) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(int index) {
    if (index >= 0 && index < user_count) {
        for (int i = index; i < user_count - 1; ++i) {
            database[i] = database[i + 1];
        }
        --user_count;
    }
}

void handle_unsubscribe_request(const char *email) {
    int index = find_user(email);
    if (index != -1) {
        delete_user(index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    handle_unsubscribe_request(email);
    return 0;
}