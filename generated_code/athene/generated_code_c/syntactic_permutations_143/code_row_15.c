#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *email;
} User;

typedef struct {
    User **users;
    int count;
} Database;

void init_database(Database *db) {
    db->users = NULL;
    db->count = 0;
}

int find_user(const Database *db, const char *email) {
    for (int i = 0; i < db->count; ++i) {
        if (strcmp(db->users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user(Database *db, int index) {
    free(db->users[index]);
    for (int i = index; i < db->count - 1; ++i) {
        db->users[i] = db->users[i + 1];
    }
    db->count--;
    if (db->count == 0) {
        free(db->users);
        db->users = NULL;
    } else {
        db->users = realloc(db->users, sizeof(User *) * db->count);
    }
}

void unsubscribe_user(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        remove_user(db, index);
        printf("User %s has been successfully unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3 || strcmp(argv[1], "unsubscribe") != 0) {
        fprintf(stderr, "Usage: %s unsubscribe <email>\n", argv[0]);
        return EXIT_FAILURE;
    }

    Database db;
    init_database(&db);

    // Example users for testing
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("user1@example.com");
    User *user2 = malloc(sizeof(User));
    user2->email = strdup("user2@example.com");

    db.users = realloc(db.users, sizeof(User *) * 2);
    db.users[0] = user1;
    db.users[1] = user2;
    db.count = 2;

    unsubscribe_user(&db, argv[2]);

    return EXIT_SUCCESS;
}