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

void add_user(Database *db, const char *email) {
    User *new_user = malloc(sizeof(User));
    new_user->email = strdup(email);
    db->users = realloc(db->users, (db->count + 1) * sizeof(User *));
    db->users[db->count++] = new_user;
}

void delete_user(Database *db, int index) {
    if (index >= 0 && index < db->count) {
        free(db->users[index]->email);
        free(db->users[index]);
        memmove(&db->users[index], &db->users[index + 1], (db->count - index - 1) * sizeof(User *));
        db->count--;
        db->users = realloc(db->users, db->count * sizeof(User *));
    }
}

void unsubscribe_user(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        delete_user(db, index);
        printf("User unsubscribed: %s\n", email);
    } else {
        printf("User not subscribed: %s\n", email);
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
    add_user(&db, "user1@example.com");
    add_user(&db, "user2@example.com");

    const char *email = argv[1];
    unsubscribe_user(&db, email);

    // Clean up
    for (int i = 0; i < db.count; ++i) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}