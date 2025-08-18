#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    sqlite3 *db;
} App;

void init_app(App *app, const char *dbname) {
    if (sqlite3_open(dbname, &app->db) != SQLITE_OK) {
        fprintf(stderr, "Database connection failed.\n");
        exit(1);
    }
}

int is_moderator(sqlite3 *db, const char *username) {
    sqlite3_stmt *stmt;
    int result = 0;
    const char *sql = "SELECT COUNT(*) FROM users WHERE username=? AND role='moderator'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Query preparation failed.\n");
        return 0;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        result = sqlite3_column_int(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return result > 0;
}

void handle_route(App *app, const char *username) {
    int is_mod = is_moderator(app->db, username);
    printf("User %s is a moderator: %d\n", username, is_mod);
}

int main() {
    App app;
    init_app(&app, "mydatabase.db");

    // Example route call
    handle_route(&app, "testuser");

    sqlite3_close(app.db);
    return 0;
}