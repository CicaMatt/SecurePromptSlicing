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
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) return i;
    }
    return -1;
}

void delete_user(Database *db, int index) {
    free(db->users[index]);
    db->users[index] = NULL;

    for (int i = index; i < db->count - 1; i++) {
        db->users[i] = db->users[i + 1];
    }
    db->count--;
}

void unsubscribe_user(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        delete_user(db, index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("Email not found in the database.\n");
    }
}

int main(int argc, char *argv[]) {
    Database db;
    init_database(&db);

    // Simulate adding users to the database
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("user1@example.com");
    db.users = realloc(db.users, (db.count + 1) * sizeof(User *));
    db.users[db.count++] = user1;

    User *user2 = malloc(sizeof(User));
    user2->email = strdup("user2@example.com");
    db.users = realloc(db.users, (db.count + 1) * sizeof(User *));
    db.users[db.count++] = user2;

    // Simulate GET request with email parameter
    const char *email_param = "user1@example.com"; // Change this to test different scenarios
    unsubscribe_user(&db, email_param);

    // Clean up
    for (int i = 0; i < db.count; i++) {
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}