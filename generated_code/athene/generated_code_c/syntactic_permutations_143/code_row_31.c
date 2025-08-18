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

Database db = {0};

void init_db() {
    db.users = (User **)malloc(10 * sizeof(User *));
    for (int i = 0; i < 10; ++i) {
        db.users[i] = (User *)malloc(sizeof(User));
        db.users[i]->email = NULL;
    }
    db.count = 10;
}

void add_user_to_db(const char *email) {
    if (db.count > 0) {
        User *user = db.users[--db.count];
        user->email = strdup(email);
    }
}

int find_user_in_db(const char *email) {
    for (int i = 0; i < 10 - db.count; ++i) {
        if (strcmp(db.users[i]->email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void delete_user_from_db(int index) {
    free(db.users[index]->email);
    free(db.users[index]);
    for (int i = index; i < 9 - db.count; ++i) {
        db.users[i] = db.users[i + 1];
    }
    db.count++;
}

void handle_unsubscribe_request(const char *email) {
    int index = find_user_in_db(email);
    if (index != -1) {
        delete_user_from_db(index);
        printf("User %s has been unsubscribed.\n", email);
    } else {
        printf("User %s is not subscribed.\n", email);
    }
}

int main(int argc, char *argv[]) {
    init_db();
    add_user_to_db("test@example.com");
    add_user_to_db("user1@example.com");

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    handle_unsubscribe_request(email);

    return 0;
}