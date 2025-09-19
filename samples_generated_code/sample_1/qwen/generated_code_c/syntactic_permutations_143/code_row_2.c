#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "mailing_list.db"

int check_and_unsubscribe(const char *email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM subscribers WHERE email = '%q';", email);

    rc = sqlite3_exec(db, query, NULL, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%q';", email);

    rc = sqlite3_exec(db, query, NULL, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_close(db);

    if (sqlite3_changes(db) == 0) {
        printf("User is not subscribed.\n");
        return 2; // User not found
    } else {
        printf("User unsubscribed successfully.\n");
        return 0; // Success
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];
    int result = check_and_unsubscribe(email);

    return result;
}