#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void unsubscribe(char *email) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("subscribers.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[256];
    sprintf(sql, "SELECT COUNT(*) FROM subscribers WHERE email='%s'", email);

    // Execute SQL query
    rc = sqlite3_exec(db, sql, [](void *data, int argc, char **argv, char **azColName) -> int {
        if (argc == 1 && atoi(argv[0]) > 0) {
            printf("User is subscribed. Unsubscribing...\n");
            return 0;
        } else {
            printf("User not found in the database.\n");
            return 0;
        }
    }, NULL, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        // If user is in the database
        char deleteSql[256];
        sprintf(deleteSql, "DELETE FROM subscribers WHERE email='%s'", email);

        rc = sqlite3_exec(db, deleteSql, 0, 0, &errMsg);
        if (rc != SQLITE_OK) {
            fprintf(stderr, "Failed to unsubscribe: %s\n", errMsg);
            sqlite3_free(errMsg);
        } else {
            printf("User unsubscribed successfully.\n");
        }
    }

    // Close database
    sqlite3_close(db);
}

int main() {
    char email[256];
    printf("Enter your email address to unsubscribe:\n");
    scanf("%255s", email);

    unsubscribe(email);

    return 0;
}