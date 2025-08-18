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

int find_user(Database *db, const char *email) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i]->email, email) == 0) return i;
    }
    return -1;
}

void delete_user(Database *db, int index) {
    free(db->users[index]);
    memmove(&db->users[index], &db->users[index + 1], sizeof(User *) * (db->count - index - 1));
    db->count--;
}

char* handle_unsubscribe(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        delete_user(db, index);
        return "User unsubscribed successfully.";
    } else {
        return "User is not subscribed.";
    }
}

int main() {
    // Simulate a GET request with an email parameter
    const char *request_email = "example@example.com";

    // Initialize a sample database
    Database db;
    db.users = (User **)malloc(3 * sizeof(User *));
    db.users[0] = (User *)malloc(sizeof(User));
    db.users[0]->email = strdup("user1@example.com");
    db.users[1] = (User *)malloc(sizeof(User));
    db.users[1]->email = strdup("user2@example.com");
    db.count = 2;

    // Handle the unsubscribe request
    char *response = handle_unsubscribe(&db, request_email);
    printf("%s\n", response);

    // Clean up
    for (int i = 0; i < db.count; i++) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}