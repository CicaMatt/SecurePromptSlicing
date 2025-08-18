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

void init_db(Database *db) {
    db->users = NULL;
    db->count = 0;
}

int find_user(Database *db, const char *email) {
    for (int i = 0; i < db->count; ++i) {
        if (strcmp(db->users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(Database *db, int index) {
    free(db->users[index]);
    for (int i = index; i < db->count - 1; ++i) {
        db->users[i] = db->users[i + 1];
    }
    db->count--;
    db->users = realloc(db->users, sizeof(User *) * db->count);
}

void handle_unsubscribe(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        delete_user(db, index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    Database db;
    init_db(&db);

    // Simulate adding users to the database
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("example@example.com");
    db.users = realloc(db.users, sizeof(User *) * (db.count + 1));
    db.users[db.count++] = user1;

    handle_unsubscribe(&db, argv[1]);

    // Clean up
    for (int i = 0; i < db.count; ++i) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}