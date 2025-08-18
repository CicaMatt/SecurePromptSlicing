#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int unsubscribe(sqlite3 *db, const char *email) {
    int rc;
    char *sql;
    char **result;
    int row, column;

    // Prepare SQL query to check if email exists in the database
    sql = sqlite3_mprintf("SELECT COUNT(*) FROM users WHERE email = '%q';", email);
    rc = sqlite3_get_table(db, sql, &result, &row, &column, NULL);
    sqlite3_free(sql);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    int count = atoi(result[1]);
    sqlite3_free_table(result);

    if (count == 0) {
        printf("Email address not found in the database.\n");
        return 0;
    }

    // Prepare SQL query to delete the email from the database
    sql = sqlite3_mprintf("DELETE FROM users WHERE email = '%q';", email);
    rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
    sqlite3_free(sql);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    printf("Email address has been successfully unsubscribed.\n");
    return 0;
}

int main() {
    sqlite3 *db;
    int rc;
    char email[256];

    // Open the database
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    rc = unsubscribe(db, email);
    if (rc == 0) {
        // Success
    } else {
        fprintf(stderr, "Unsubscription failed.\n");
    }

    sqlite3_close(db);
    return 0;
}