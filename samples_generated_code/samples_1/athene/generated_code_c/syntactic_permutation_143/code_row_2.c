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
    if (db->count == 0) {
        free(db->users);
        db->users = NULL;
    } else {
        db->users = realloc(db->users, sizeof(User *) * db->count);
    }
}

void handle_unsubscribe_request(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        delete_user(db, index);
        printf("User unsubscribed: %s\n", email);
    } else {
        printf("User not subscribed: %s\n", email);
    }
}

int main() {
    Database db;
    init_database(&db);

    // Example users in the database
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("user1@example.com");
    User *user2 = malloc(sizeof(User));
    user2->email = strdup("user2@example.com");

    db.users = realloc(db.users, sizeof(User *) * 2);
    db.users[0] = user1;
    db.users[1] = user2;
    db.count = 2;

    // Simulate GET request with email parameter
    const char *email_to_unsubscribe = "user1@example.com";
    handle_unsubscribe_request(&db, email_to_unsubscribe);

    return 0;
}