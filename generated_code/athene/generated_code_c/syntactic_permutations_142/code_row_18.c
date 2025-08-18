#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(sqlite3 *db, const char *email) {
    int rc;
    char *err_msg = 0;
    const char *sql = "DELETE FROM subscribers WHERE email = ?;";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    sqlite3_bind_text(stmt, 1, email, -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to unsubscribe user: %s\n", err_msg ? err_msg : sqlite3_errmsg(db));
    } else {
        printf("Unsubscribed successfully.\n");
    }

    sqlite3_finalize(stmt);

    return rc == SQLITE_DONE ? 0 : 1;
}

int main() {
    sqlite3 *db;
    int rc;

    const char *email = "user@example.com";

    rc = sqlite3_open("subscriptions.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return rc;
    }

    rc = unsubscribe(db, email);
    if (rc != 0) {
        fprintf(stderr, "Unsubscription failed.\n");
    }

    sqlite3_close(db);

    return 0;
}