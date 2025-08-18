#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int unsubscribeUser(sqlite3 *db, const char *email) {
    char *errMsg = NULL;
    int rc;

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE email='%s'", email);

    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return -1;
    }

    char result[64];
    snprintf(sql, sizeof(sql), "SELECT COUNT(*) FROM users WHERE email='%s'", email);
    rc = sqlite3_exec(db, sql, (void (*)(void*, int, char**, char**))callback_user_count, &result, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return -1;
    }

    if (strcmp(result, "0") == 0) {
        printf("User with email '%s' is not subscribed.\n", email);
        return 0;
    } else {
        snprintf(sql, sizeof(sql), "DELETE FROM users WHERE email='%s'", email);
        
        rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", errMsg);
            sqlite3_free(errMsg);
            return -1;
        }

        printf("User with email '%s' has been unsubscribed.\n", email);
        return 1;
    }
}

static int callback_user_count(void *data, int argc, char **argv, char **azColName) {
    if (argc == 1) {
        strcpy((char *)data, argv[0]);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    sqlite3 *db;
    const char *dbName = "database.db";
    const char *email;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <email>\n", argv[0]);
        return -1;
    }

    email = argv[1];

    int rc = sqlite3_open(dbName, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    unsubscribeUser(db, email);

    sqlite3_close(db);
    return 0;
}