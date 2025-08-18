#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    const char *sql;
    char query[100];
    char *zErrMsg = 0;

    // Open database
    rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    sprintf(query, "SELECT COUNT(*) FROM users WHERE email='%s';", email);
    sql = query;

    // Execute SQL
    rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        int count;
        sqlite3_stmt *res;
        rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

        if (rc == SQLITE_OK) {
            while (sqlite3_step(res) == SQLITE_ROW) {
                count = sqlite3_column_int(res, 0);
                if (count > 0) {
                    // Email exists in the database
                    printf("Unsubscribing %s...\n", email);
                    sprintf(query, "DELETE FROM users WHERE email='%s';", email);
                    rc = sqlite3_exec(db, query, NULL, 0, &zErrMsg);
                    if (rc != SQLITE_OK) {
                        fprintf(stderr, "SQL error: %s\n", zErrMsg);
                        sqlite3_free(zErrMsg);
                    }
                } else {
                    // Email does not exist in the database
                    printf("Email address not found. You are already unsubscribed.\n");
                }
            }
        }

        sqlite3_finalize(res);
    }

    // Close database
    sqlite3_close(db);
}

int main() {
    char email[100];
    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email); // Limit input size to prevent buffer overflow

    unsubscribe(email);

    return 0;
}