#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

#define EMAIL_MAX_LENGTH 254

int unsubscribe(sqlite3 *db, const char *email) {
    int rc;
    char sql[100 + EMAIL_MAX_LENGTH];
    snprintf(sql, sizeof(sql), "DELETE FROM subscribers WHERE email='%s';", email);
    
    rc = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (rc != SQLITE_OK) {
        return 0; // Email not found
    }
    
    int count;
    sqlite3_stmt *stmt;
    const char *sql_check = "SELECT changes();";
    rc = sqlite3_prepare_v2(db, sql_check, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        return 0; // Error checking changes
    }
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    } else {
        count = 0;
    }
    
    sqlite3_finalize(stmt);
    return count > 0 ? 1 : 0; // Return 1 if deleted, 0 otherwise
}

int main() {
    sqlite3 *db;
    int rc;
    char email[EMAIL_MAX_LENGTH + 1];

    printf("Enter your email address to unsubscribe: ");
    scanf("%254s", email);

    rc = sqlite3_open("subscribers.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int result = unsubscribe(db, email);
    
    if (result == 1) {
        printf("You have been successfully unsubscribed.\n");
    } else {
        printf("Email address not found in the database. You are already unsubscribed.\n");
    }

    sqlite3_close(db);
    return 0;
}