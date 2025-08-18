#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "subscribers.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int is_email_in_database(const char *email) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM subscribers WHERE email = '%q';", email);

    rc = sqlite3_exec(db, query, callback, 0, &err_msg);
    if (rc == SQLITE_OK) {
        int row_count = sqlite3_changes(db);
        sqlite3_close(db);
        return row_count > 0;
    } else {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 0;
    }
}

void delete_email_from_database(const char *email) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%q';", email);

    rc = sqlite3_exec(db, query, callback, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
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
        delete_email_from_database(email);
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }

    return 0;
}