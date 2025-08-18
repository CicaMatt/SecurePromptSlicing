#include <stdio.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

void insert_user(sqlite3 *db, const char *username, const char *password) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password) VALUES ('%s', '%s');", username, password);
    sqlite3_exec(db, sql, callback, 0, NULL);
}

int main() {
    sqlite3 *db;
    int rc;
    const char *database = "test.db";
    const char *sql;

    rc = sqlite3_open(database, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, password TEXT);";
    rc = sqlite3_exec(db, sql, callback, 0, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    insert_user(db, username, password);

    sqlite3_close(db);
    return 0;
}