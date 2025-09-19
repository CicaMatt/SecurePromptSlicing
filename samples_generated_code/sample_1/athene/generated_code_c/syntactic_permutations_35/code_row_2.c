#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *username;
    char *password;
} User;

typedef struct {
    User *users;
    int count;
} Database;

void init_database(Database *db, const char *usernames[], const char *passwords[], int count) {
    db->count = count;
    db->users = malloc(count * sizeof(User));
    for (int i = 0; i < count; i++) {
        db->users[i].username = strdup(usernames[i]);
        db->users[i].password = strdup(passwords[i]);
    }
}

int check_credentials(Database *db, const char *username, const char *password) {
    for (int i = 0; i < db->count; i++) {
        if (strcmp(db->users[i].username, username) == 0 && strcmp(db->users[i].password, password) == 0) {
            return 1;
        }
    }
    return 0;
}

void login(const char *username, const char *password, Database *db) {
    if (check_credentials(db, username, password)) {
        printf("Location: /home.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Welcome to the home page!</body></html>");
    } else {
        printf("Location: /login.html\n");
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login failed. Please try again.</body></html>");
    }
}

int main() {
    const char *usernames[] = {"user1", "user2"};
    const char *passwords[] = {"pass1", "pass2"};
    int count = 2;

    Database db;
    init_database(&db, usernames, passwords, count);

    // Simulate form submission
    const char *username = getenv("HTTP_USERNAME");
    const char *password = getenv("HTTP_PASSWORD");

    if (username != NULL && password != NULL) {
        login(username, password, &db);
    } else {
        printf("Content-Type: text/html\n\n");
        printf("<html><body>Login form not submitted correctly.</body></html>");
    }

    // Free allocated memory
    for (int i = 0; i < db.count; i++) {
        free(db.users[i].username);
        free(db.users[i].password);
    }
    free(db.users);

    return 0;
}