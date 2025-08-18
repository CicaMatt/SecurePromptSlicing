#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char *zErrMsg = 0;

    // Open database
    rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    // Check if email exists in the database
    sql = "SELECT COUNT(*) FROM subscribers WHERE email=?;";
    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_text(res, 1, email, -1, SQLITE_STATIC);
        int count = 0;
        while (sqlite3_step(res) == SQLITE_ROW) {
            count = sqlite3_column_int(res, 0);
        }
        sqlite3_finalize(res);

        if (count > 0) {
            // Remove the email from the database
            sql = "DELETE FROM subscribers WHERE email=?;";
            rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
            if (rc == SQLITE_OK) {
                sqlite3_bind_text(res, 1, email, -1, SQLITE_STATIC);
                rc = sqlite3_step(res);
                if (rc != SQLITE_DONE) {
                    fprintf(stderr, "Failed to delete record: %s\n", zErrMsg);
                }
            } else {
                fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
            }
            sqlite3_finalize(res);
            printf("You have been unsubscribed.\n");
        } else {
            printf("This email address is not in our database.\n");
        }
    } else {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    // Close the database connection
    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email address to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}