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

int add_user(Database *db, const char *email) {
    User *user = (User *)malloc(sizeof(User));
    if (!user) return -1;
    user->email = strdup(email);
    db->users = (User **)realloc(db->users, (db->count + 1) * sizeof(User *));
    if (!db->users) {
        free(user);
        return -1;
    }
    db->users[db->count++] = user;
    return 0;
}

int find_user(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_user(Database *db, int index) {
    free(db->users[index]->email);
    free(db->users[index]);
    for (int i = index; i < db->count - 1; i++) {
        db->users[i] = db->users[i + 1];
    }
    db->count--;
    db->users = (User **)realloc(db->users, db->count * sizeof(User *));
}

void handle_unsubscribe(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        remove_user(db, index);
        printf("You have been unsubscribed successfully.\n");
    } else {
        printf("Email not found in the database.\n");
    }
}

void free_database(Database *db) {
    for (int i = 0; i < db->count; i++) {
        free(db->users[i]->email);
        free(db->users[i]);
    }
    free(db->users);
}

int main() {
    Database db;
    init_database(&db);

    // Example: Adding some users to the database
    add_user(&db, "user1@example.com");
    add_user(&db, "user2@example.com");

    const char *email = "user2@example.com"; // This would come from a GET request parameter in a real application
    handle_unsubscribe(&db, email);

    free_database(&db);
    return 0;
}