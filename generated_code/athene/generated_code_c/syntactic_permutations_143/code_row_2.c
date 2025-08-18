#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char *email;
} User;

typedef struct {
    User **users;
    int count;
} Database;

void initDatabase(Database *db) {
    db->users = NULL;
    db->count = 0;
}

int addUser(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) return 0;
    }
    User *user = malloc(sizeof(User));
    user->email = strdup(email);
    db->users = realloc(db->users, (db->count + 1) * sizeof(User *));
    db->users[db->count++] = user;
    return 1;
}

int deleteUser(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) {
            free(db->users[i]->email);
            free(db->users[i]);
            for (; i < db->count - 1; i++) {
                db->users[i] = db->users[i + 1];
            }
            db->users = realloc(db->users, (db->count - 1) * sizeof(User *));
            db->count--;
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 3 || strcmp(argv[1], "unsubscribe") != 0) {
        printf("Usage: %s unsubscribe <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[2];
    Database db;
    initDatabase(&db);

    // Simulate adding some users to the database
    addUser(&db, "user1@example.com");
    addUser(&db, "user2@example.com");

    if (deleteUser(&db, email)) {
        printf("You have been unsubscribed.\n");
    } else {
        printf("You are not subscribed.\n");
    }

    for (int i = 0; i < db.count; i++) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}