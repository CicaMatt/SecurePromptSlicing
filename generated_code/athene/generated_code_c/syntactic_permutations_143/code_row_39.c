#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMAIL_LENGTH 256

typedef struct {
    char email[MAX_EMAIL_LENGTH];
} User;

typedef struct {
    User *users;
    int count;
} Database;

int find_user(Database *db, const char *email) {
    for (int i = 0; i < db->count; ++i) {
        if (strcmp(db->users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(Database *db, int index) {
    if (index >= 0 && index < db->count) {
        for (int i = index; i < db->count - 1; ++i) {
            db->users[i] = db->users[i + 1];
        }
        --db->count;
    }
}

void handle_unsubscribe(Database *db, const char *email) {
    int index = find_user(db, email);
    if (index != -1) {
        delete_user(db, index);
        printf("User unsubscribed successfully.\n");
    } else {
        printf("User not found in the database.\n");
    }
}

int main() {
    // Mock database initialization
    Database db;
    db.count = 2;
    db.users = (User *)malloc(db.count * sizeof(User));
    strcpy(db.users[0].email, "user1@example.com");
    strcpy(db.users[1].email, "user2@example.com");

    // Simulate GET request with email parameter
    char email[MAX_EMAIL_LENGTH];
    printf("Enter email to unsubscribe: ");
    scanf("%s", email);

    handle_unsubscribe(&db, email);

    free(db.users);
    return 0;
}