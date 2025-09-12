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

int findUserByEmail(Database *db, const char *email) {
    for (int i = 0; i < db->count; ++i) {
        if (strcmp(db->users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void deleteUserFromDatabase(Database *db, int index) {
    free(db->users[index]);
    for (int i = index; i < db->count - 1; ++i) {
        db->users[i] = db->users[i + 1];
    }
    --db->count;
}

void handleUnsubscribeRequest(Database *db, const char *email) {
    int index = findUserByEmail(db, email);
    if (index != -1) {
        deleteUserFromDatabase(db, index);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }
}

int main() {
    // Simulate database initialization
    Database db;
    User *user1 = malloc(sizeof(User));
    user1->email = strdup("test@example.com");
    User *user2 = malloc(sizeof(User));
    user2->email = strdup("example@test.com");

    db.users = malloc(2 * sizeof(User *));
    db.users[0] = user1;
    db.users[1] = user2;
    db.count = 2;

    // Simulate GET request with email parameter
    const char *requestEmail = "test@example.com";
    handleUnsubscribeRequest(&db, requestEmail);

    // Clean up
    for (int i = 0; i < db.count; ++i) {
        free(db.users[i]->email);
        free(db.users[i]);
    }
    free(db.users);

    return 0;
}