#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LEN 254

typedef struct {
    char email[MAX_EMAIL_LEN];
    int subscribed;
} User;

typedef struct {
    User users[100];
    int count;
} Database;

Database db = { .count = 0 };

int find_user(const char *email) {
    for (int i = 0; i < db.count; i++) {
        if (strcmp(db.users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void handle_unsubscribe(const char *email) {
    int index = find_user(email);
    if (index != -1 && db.users[index].subscribed) {
        db.users[index].subscribed = 0;
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed or does not exist in the database.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *email = argv[1];
    handle_unsubscribe(email);
    return EXIT_SUCCESS;
}