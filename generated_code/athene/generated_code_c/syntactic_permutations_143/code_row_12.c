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

int find_user_index(Database *db, const char *email) {
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
    int index = find_user_index(db, email);
    if (index == -1) {
        printf("User is not subscribed.\n");
    } else {
        delete_user(db, index);
        printf("User unsubscribed successfully.\n");
    }
}

int main() {
    Database db;
    init_database(&db);

    // Example users
    User *user1 = (User *)malloc(sizeof(User));
    user1->email = strdup("user1@example.com");
    User *user2 = (User *)malloc(sizeof(User));
    user2->email = strdup("user2@example.com");

    db.users = (User **)realloc(db.users, sizeof(User *) * 2);
    db.users[0] = user1;
    db.users[1] = user2;
    db.count = 2;

    // Simulate GET request with email parameter
    const char *email_param = "user2@example.com";
    handle_unsubscribe(&db, email_param);

    // Clean up
    for (int i = 0; i < db.count; ++i) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}