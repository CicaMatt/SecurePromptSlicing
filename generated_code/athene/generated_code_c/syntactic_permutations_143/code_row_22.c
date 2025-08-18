#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *email;
} User;

typedef struct {
    User **users;
    size_t count;
} Database;

void init_database(Database *db) {
    db->count = 0;
    db->users = NULL;
}

int find_user(const Database *db, const char *email) {
    for (size_t i = 0; i < db->count; ++i) {
        if (strcmp(db->users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user(Database *db, int index) {
    free(db->users[index]);
    memmove(&db->users[index], &db->users[index + 1], (db->count - index - 1) * sizeof(User *));
    db->count--;
    db->users = realloc(db->users, db->count * sizeof(User *));
}

void handle_unsubscribe(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        remove_user(db, index);
        printf("Unsubscribed: %s\n", email);
    } else {
        printf("Not subscribed: %s\n", email);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    Database db;
    init_database(&db);

    // Example users for testing
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("example1@example.com");
    User *user2 = malloc(sizeof(User));
    user2->email = strdup("example2@example.com");

    db.users = realloc(db.users, 2 * sizeof(User *));
    db.users[0] = user1;
    db.users[1] = user2;
    db.count = 2;

    handle_unsubscribe(&db, argv[1]);

    // Clean up
    for (size_t i = 0; i < db.count; ++i) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}