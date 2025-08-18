#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATABASE_SIZE 10

typedef struct {
    char email[50];
    int subscribed;
} User;

User database[DATABASE_SIZE] = {
    {"user1@example.com", 1},
    {"user2@example.com", 1},
    {"user3@example.com", 1},
    {"user4@example.com", 1},
    {"user5@example.com", 0},
    {"user6@example.com", 0},
    {"user7@example.com", 1},
    {"user8@example.com", 0},
    {"user9@example.com", 1},
    {"user10@example.com", 0}
};

int findUserIndexByEmail(const char *email) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].email, email) == 0) {
            return i;
        }
    }
    return -1;
}

void unsubscribeUser(int index) {
    if (index != -1 && database[index].subscribed == 1) {
        database[index].subscribed = 0;
        printf("User %s has been unsubscribed from the mailing list.\n", database[index].email);
    } else {
        printf("The user is not subscribed.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int index = findUserIndexByEmail(email);
    unsubscribeUser(index);

    return 0;
}