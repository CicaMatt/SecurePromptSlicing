#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "app.db"

void checkUserModerator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT is_moderator FROM users WHERE username=?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC);
        
        int rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int is_moderator = sqlite3_column_int(stmt, 0);
            printf("User %s is %smoderator.\n", username, is_moderator ? "" : "not a ");
        } else {
            printf("User %s not found or error occurred.\n", username);
        }
        
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Define a route and call function when accessed
    char username[] = "example_user";
    checkUserModerator(db, username);

    sqlite3_close(db);
    return 0;
}
