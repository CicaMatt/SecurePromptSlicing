#include <stdio.h>
#include <sqlite3.h>

int main() {
    sqlite3 *db;
    int rc;
    char *zErrMsg = 0;
    const char *sql;

    // Open database
    rc = sqlite3_open("test.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    // Create table
    sql = "CREATE TABLE IF NOT EXISTS users ("  \
          "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
          "USERNAME TEXT NOT NULL," \
          "PASSWORD TEXT NOT NULL);";
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    char username[50];
    char password[] = "password123"; // Fixed password

    printf("Enter username: ");
    scanf("%49s", username);

    // Insert data
    sql = sqlite3_mprintf("INSERT INTO users (USERNAME, PASSWORD) VALUES ('%q', '%q');", username, password);
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("User registered successfully.\n");
    }

    sqlite3_close(db);
    return 0;
}