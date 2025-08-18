#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int check_credentials(sqlite3 *db, const char *username, const char *password) {
    int auth = 0;
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND password=?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
            auth = 1;
        }

        sqlite3_finalize(stmt);
    }
    return auth;
}

int main() {
    char username[100], password[100];
    printf("Content-Type: text/html\r\n\r\n");

    // Simulate reading form data
    const char *form_data = "username=admin&password=admin";
    sscanf(form_data, "username=%[^&]&password=%s", username, password);

    sqlite3 *db;
    if (sqlite3_open("database.db", &db) != SQLITE_OK) {
        printf("<html><body>Database error</body></html>");
        return 1;
    }

    if (check_credentials(db, username, password)) {
        printf("<html><head><meta http-equiv='refresh' content='0;url=home.html'/></head></html>");
    } else {
        printf("<html><head><meta http-equiv='refresh' content='0;url=login.html'/></head></html>");
    }

    sqlite3_close(db);
    return 0;
}