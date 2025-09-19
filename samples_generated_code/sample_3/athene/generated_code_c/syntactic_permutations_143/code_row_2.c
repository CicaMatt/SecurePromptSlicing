#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *email;
} User;

typedef struct {
    User **users;
    int size;
    int capacity;
} Database;

void init_database(Database *db, int capacity) {
    db->capacity = capacity;
    db->size = 0;
    db->users = malloc(capacity * sizeof(User *));
}

int find_user(Database *db, const char *email) {
    for (int i = 0; i < db->size; i++) {
        if (strcmp(db->users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(Database *db, int index) {
    free(db->users[index]->email);
    free(db->users[index]);
    for (int i = index; i < db->size - 1; i++) {
        db->users[i] = db->users[i + 1];
    }
    db->size--;
}

void handle_unsubscribe(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        delete_user(db, index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    Database db;
    init_database(&db, 10);

    // Example data
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("example1@example.com");
    db.users[db.size++] = user1;

    char email_param[] = "example1@example.com";
    handle_unsubscribe(&db, email_param);

    for (int i = 0; i < db.capacity; i++) {
        if (db.users[i] != NULL) {
            free(db.users[i]->email);
            free(db.users[i]);
        }
    }
    free(db.users);

    return 0;
}