#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "users.db"
#define TABLE_NAME "subscribers"

int unsubscribe(const char *email) {
    sqlite3 *db;
    int rc;
    char *sql, *zErrMsg;

    // Open database
    rc = sqlite3_open(DATABASE, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Prepare SQL statement to check and delete email
    sql = sqlite3_mprintf("DELETE FROM %s WHERE email='%q';", TABLE_NAME, email);
    rc = sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        sqlite3_close(db);
        return 1;
    }

    // Check if any rows were affected
    int rows_deleted = sqlite3_changes(db);
    sqlite3_close(db);

    return rows_deleted == 0 ? 1 : 0; // Return 0 for success, 1 for failure
}

int main() {
    char email[256];
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    if (unsubscribe(email) == 0) {
        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("Email not found or an error occurred.\n");
    }

    return 0;
}