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

Database db = {NULL, 0};

void init_database() {
    // Example initialization
    db.users = malloc(10 * sizeof(User));
    strcpy(db.users[0].email, "user@example.com");
    db.count = 1;
}

int find_user(const char *email) {
    for (int i = 0; i < db.count; i++) {
        if (strcmp(db.users[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user(int index) {
    if (index >= 0 && index < db.count) {
        for (int i = index; i < db.count - 1; i++) {
            db.users[i] = db.users[i + 1];
        }
        db.count--;
    }
}

void handle_unsubscribe(const char *email) {
    int index = find_user(email);
    if (index != -1) {
        delete_user(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User is not subscribed.\n");
    }
}

int main() {
    init_database();
    
    char email[MAX_EMAIL_LENGTH];
    printf("Enter email to unsubscribe: ");
    scanf("%255s", email);

    handle_unsubscribe(email);

    free(db.users);
    return 0;
}