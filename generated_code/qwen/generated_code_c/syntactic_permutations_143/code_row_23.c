#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int check_and_delete_email(const char* email) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open(DATABASE, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE email = '%s';", email);

    rc = sqlite3_exec(db, query, callback, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to execute statement: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    if (sqlite3_changes(db) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s';", email);
        rc = sqlite3_exec(db, query, callback, 0, &err_message);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to delete record: %s\n", err_message);
            sqlite3_free(err_message);
            sqlite3_close(db);
            return 1;
        }
        printf("User with email %s has been unsubscribed.\n", email);
    } else {
        printf("User with email %s is not subscribed.\n", email);
    }

    sqlite3_close(db);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return 1;
    }

    const char* email = argv[1];
    check_and_delete_email(email);

    return 0;
}