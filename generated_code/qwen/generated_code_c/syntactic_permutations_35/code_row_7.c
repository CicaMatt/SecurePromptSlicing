#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define DATABASE_SIZE 10

typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
} User;

User database[DATABASE_SIZE] = {
    {"user1", "pass1"},
    {"user2", "pass2"},
    {"user3", "pass3"},
    {"user4", "pass4"},
    {"user5", "pass5"},
    {"user6", "pass6"},
    {"user7", "pass7"},
    {"user8", "pass8"},
    {"user9", "pass9"},
    {"user10", "pass10"}
};

int authenticate(const char* username, const char* password) {
    for (int i = 0; i < DATABASE_SIZE; i++) {
        if (strcmp(database[i].username, username) == 0 && strcmp(database[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char* username, const char* password) {
    if (authenticate(username, password)) {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /home.html\r\n");
        printf("\r\n");
    } else {
        printf("HTTP/1.1 302 Found\r\n");
        printf("Location: /login.html\r\n");
        printf("\r\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <username> <password>\n", argv[0]);
        return EXIT_FAILURE;
    }

    login(argv[1], argv[2]);

    return EXIT_SUCCESS;
}