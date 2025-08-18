#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simulated database of users for demonstration purposes
typedef struct {
    char username[50];
    char password[50];
    int is_moderator; // 1 if moderator, 0 otherwise
} User;

User users[] = {
    {"alice", "password123", 1},
    {"bob", "qwerty", 0}
};

int auth_mod(const char *username, const char *password) {
    for (int i = 0; i < sizeof(users) / sizeof(User); ++i) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            return users[i].is_moderator;
        }
    }
    return 0;
}

void check_mod(const char *username, const char *password, const char *session) {
    int is_moderator = auth_mod(username, password);
    if (is_moderator) {
        printf("User %s with session %s is a moderator.\n", username, session);
    } else {
        printf("User %s with session %s is not a moderator.\n", username, session);
    }
}

// Simulating URL parsing by calling check_mod() directly
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <username> <password> <session>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *username = argv[1];
    const char *password = argv[2];
    const char *session = argv[3];

    check_mod(username, password, session);

    return EXIT_SUCCESS;
}