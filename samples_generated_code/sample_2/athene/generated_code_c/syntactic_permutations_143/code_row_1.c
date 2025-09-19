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

int find_user_index(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(Database *db, int index) {
    if (index >= 0 && index < db->count) {
        free(db->users[index]);
        for (int i = index; i < db->count - 1; i++) {
            db->users[i] = db->users[i + 1];
        }
        db->count--;
        db->users = realloc(db->users, sizeof(User *) * db->count);
    }
}

void handle_unsubscribe(Database *db, const char *email) {
    int index = find_user_index(db, email);
    if (index != -1) {
        delete_user(db, index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    Database db;
    init_database(&db);

    // Example users
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("john@example.com");
    User *user2 = malloc(sizeof(User));
    user2->email = strdup("jane@example.com");

    db.users = realloc(db.users, sizeof(User *) * 2);
    db.users[0] = user1;
    db.users[1] = user2;
    db.count = 2;

    handle_unsubscribe(&db, argv[1]);

    // Clean up
    for (int i = 0; i < db.count; i++) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}