#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

int main() {
    sqlite3 *db;
    char *errMsg = NULL;
    const char *sql;
    char email[256];

    printf("Enter your email address to unsubscribe: ");
    if (fgets(email, sizeof(email), stdin) != NULL) {
        // Remove newline character from the input
        size_t len = strlen(email);
        if (len > 0 && email[len - 1] == '\n') {
            email[--len] = '\0';
        }
        
        int rc;
        
        // Open database connection
        rc = sqlite3_open("subscribers.db", &db);
        if (rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return 1;
        }

        // Check if email is in the database
        sql = "SELECT COUNT(*) FROM subscribers WHERE email = ?";
        char *sqlErrMsg;

        int count = 0;
        rc = sqlite3_exec(db, sql, [](void *data, int argc, char **argv, char **azColName) -> int {
            if (argc > 0) *((int *)data) = atoi(argv[0]);
            return 0;
        }, &count, &sqlErrMsg);

        if (rc != SQLITE_OK) {
            fprintf(stderr, "SQL error: %s\n", sqlErrMsg);
            sqlite3_free(sqlErrMsg);
            sqlite3_close(db);
            return 1;
        }

        // If email exists in the database
        if (count > 0) {
            printf("Removing your subscription...\n");
            
            sql = "DELETE FROM subscribers WHERE email = ?";
            rc = sqlite3_exec(db, sql, callback, 0, &sqlErrMsg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", sqlErrMsg);
                sqlite3_free(sqlErrMsg);
            } else {
                printf("Your subscription has been removed.\n");
            }
        } else {
            printf("Email address not found in the database.\n");
        }

        // Close the database connection
        sqlite3_close(db);
    }
    
    return 0;
}