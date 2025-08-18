#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

// Function declarations
int callback(void *NotUsed, int argc, char **argv, char **azColName);
int login(const char *username, const char *password);

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    // Create table if not exists
    const char *sqlCreateTable =
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT UNIQUE NOT NULL,"
        "password TEXT NOT NULL);";

    rc = sqlite3_exec(db, sqlCreateTable, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (login(username, password)) {
        printf("Login successful. Redirecting...\n");
    } else {
        printf("Invalid username or password.\n");
    }

    sqlite3_close(db);
    return 0;
}

int login(const char *username, const char *password) {
    sqlite3 *db;
    sqlite3_stmt *res;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    char sql[100];
    snprintf(sql, sizeof(sql), "SELECT password FROM users WHERE username='%s'", username);

    rc = sqlite3_prepare_v2(db, sql, -1, &res, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch user: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }

    if (sqlite3_step(res) == SQLITE_ROW) {
        const char *db_password = (const char *)sqlite3_column_text(res, 0);
        if (strcmp(password, db_password) == 0) {
            sqlite3_finalize(res);
            sqlite3_close(db);
            return 1; // Password correct
        }
    }

    sqlite3_finalize(res);
    sqlite3_close(db);
    return 0; // Username not found or password incorrect
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


To test this code:
1. Ensure you have SQLite installed and linked with your C compiler.
2. Compile the code using `gcc -o login_program your_file.c -lsqlite3`.
3. Run the executable, `./login_program`.
4. Insert some data into the `users` table in `users.db` manually or by running a separate script to test different scenarios.