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

int add_user(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) return 0;
    }
    User *user = malloc(sizeof(User));
    user->email = strdup(email);
    db->users = realloc(db->users, sizeof(User *) * (db->count + 1));
    db->users[db->count++] = user;
    return 1;
}

int remove_user(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) {
            free(db->users[i]->email);
            free(db->users[i]);
            for (; i < db->count - 1; i++) {
                db->users[i] = db->users[i + 1];
            }
            db->count--;
            db->users = realloc(db->users, sizeof(User *) * db->count);
            return 1;
        }
    }
    return 0;
}

int is_user_in_database(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) return 1;
    }
    return 0;
}

void handle_unsubscribe_request(const char *email, Database *db) {
    if (is_user_in_database(db, email)) {
        remove_user(db, email);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main() {
    Database db;
    init_database(&db);

    add_user(&db, "alice@example.com");
    add_user(&db, "bob@example.com");

    char *email = "alice@example.com";
    handle_unsubscribe_request(email, &db);

    for (int i = 0; i < db.count; i++) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}