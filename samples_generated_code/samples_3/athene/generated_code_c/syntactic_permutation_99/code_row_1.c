#include <stdio.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("  \
        "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
        "USERNAME TEXT NOT NULL," \
        "PASSWORD TEXT NOT NULL);";

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Table created successfully\n");
    }

    char *insert_sql = "INSERT INTO users (USERNAME, PASSWORD) VALUES (?, ?);";
    sqlite3_stmt *stmt;

    rc = sqlite3_prepare_v2(db, insert_sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Records created successfully\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}