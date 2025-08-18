#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int unsubscribe_user(const char *email) {
    sqlite3 *db;
    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s';", email);

    rc = sqlite3_exec(db, query, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    int changes = sqlite3_changes(db);
    sqlite3_close(db);

    if (changes == 0) {
        printf("User is not subscribed.\n");
        return 2;
    } else {
        printf("User unsubscribed successfully.\n");
        return 0;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int result = unsubscribe_user(email);

    return result;
}