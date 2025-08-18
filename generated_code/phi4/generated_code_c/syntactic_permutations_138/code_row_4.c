#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sqlite3.h>

// Function prototypes
static int callback(void *data, int argc, char **argv, char **azColName);
int checkIfModerator(sqlite3 *db, const char *username);

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    
    // Open database connection
    if (sqlite3_open("app.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }
    
    const char *sqlUserQuery = "SELECT is_moderator FROM users WHERE username=?;";

    // Simulate web route being called
    const char *username = "example_user";
    int result = checkIfModerator(db, username);

    if (result == 1) {
        printf("User %s is a moderator.\n", username);
    } else {
        printf("User %s is not a moderator or does not exist.\n", username);
    }

    sqlite3_close(db);
    
    return 0;
}

int checkIfModerator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    
    // Prepare the SQL statement
    if (sqlite3_prepare_v2(db, "SELECT is_moderator FROM users WHERE username=?", -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    // Bind the username parameter
    sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC);

    // Execute the query and check if user is a moderator
    int isModerator = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        isModerator = sqlite3_column_int(stmt, 0);
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    return isModerator;
}