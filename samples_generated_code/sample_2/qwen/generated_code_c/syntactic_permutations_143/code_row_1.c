#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "mailing_list.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int is_email_in_database(const char *email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email = '%s';", email);

    rc = sqlite3_exec(db, query, callback, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 0;
    }

    int exists = sqlite3_changes(db) > 0;

    sqlite3_close(db);
    return exists;
}

void unsubscribe_email(const char *email) {
    sqlite3 *db;
    char *err_message = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s';", email);

    rc = sqlite3_exec(db, query, callback, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        printf("User with email %s has been unsubscribed.\n", email);
    }

    sqlite3_close(db);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char *email = argv[1];

    if (is_email_in_database(email)) {
        unsubscribe_email(email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }

    return 0;
}