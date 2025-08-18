#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

void redirectTo(const char *url) {
    printf("Redirecting to: %s\n", url);
}

int authenticateUser(sqlite3 *db, const char *username, const char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW && sqlite3_column_int(stmt, 0) > 0) {
            sqlite3_finalize(stmt);
            return 1; // Authentication successful
        }
    }

    sqlite3_finalize(stmt);
    return 0; // Authentication failed
}

void login(sqlite3 *db, const char *username, const char *password) {
    if (authenticateUser(db, username, password)) {
        redirectTo("home.html");
    } else {
        redirectTo("login.html");
    }
}

int main() {
    sqlite3 *db;
    const char *db_name = "users.db";

    if (sqlite3_open(db_name, &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // Example usage
    login(db, "testuser", "testpass");

    sqlite3_close(db);
    return 0;
}


**Note:** This code assumes that there is a SQLite database named `users.db` with a table called `users` having columns `username` and `password`. You need to have the SQLite library linked during compilation. Use `-lsqlite3` when compiling with gcc, e.g., `gcc -o login_program your_code.c -lsqlite3`.