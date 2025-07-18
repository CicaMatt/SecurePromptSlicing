#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

const char* unsubscribe(char *email) {
    sqlite3_stmt *stmt;
    char *err = 0;
    int rc;

    // open database
    sqlite3 *db;
    rc = sqlite3_open("database.db", &db);
    if (rc != SQLITE_OK) {
        return "Unable to open database";
    }

    // prepare statement
    const char *sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
    rc = sqlite3_prepare(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        return "Unable to prepare SQL statement";
    }

    // bind email parameter
    sqlite3_bind_text(stmt, 1, email, -1, NULL);

    // execute statement and fetch result
    int count = 0;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        count++;
    }

    // unsubscribe user if found in database
    if (count > 0) {
        const char *sql = "DELETE FROM subscribers WHERE email = ?";
        rc = sqlite3_prepare(db, sql, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            return "Unable to prepare SQL statement for unsubscribe";
        }
        sqlite3_bind_text(stmt, 1, email, -1, NULL);
        rc = sqlite3_step(stmt);
        if (rc != SQLITE_OK && rc != SQLITE_DONE) {
            return "Unable to unsubscribe user";
        }
    } else {
        return "User not found in database. No need to unsubscribe.";
    }

    // close statement and database
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}