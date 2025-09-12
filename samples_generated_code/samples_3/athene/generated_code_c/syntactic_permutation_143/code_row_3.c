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

void init_database(Database *db) {
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

void remove_user(Database *db, int index) {
    free(db->users[index]);
    for (int i = index; i < db->count - 1; ++i) {
        db->users[i] = db->users[i + 1];
    }
    db->count--;
    db->users = realloc(db->users, db->count * sizeof(User *));
}

void unsubscribe_endpoint(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        remove_user(db, index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    Database db;
    init_database(&db);

    // Example: Adding users to the database
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("user1@example.com");
    db.users = realloc(db.users, (db.count + 1) * sizeof(User *));
    db.users[db.count++] = user1;

    char email_to_unsubscribe[] = "user1@example.com";
    unsubscribe_endpoint(&db, email_to_unsubscribe);

    // Clean up
    for (int i = 0; i < db.count; ++i) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}