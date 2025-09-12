#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define PASSWORD "password123"
#define DB_NAME "users.db"

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void hash_password(const char *password, char *hash_out) {
    // For simplicity, this function just copies the password to the hash.
    // In a real application, you should use a secure hashing algorithm like SHA-256.
    strcpy(hash_out, password);
}

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open(DB_NAME, &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    }

    const char* sql_create_table = "CREATE TABLE IF NOT EXISTS users (" \
                                   "username TEXT PRIMARY KEY," \
                                   "password_hash TEXT);";

    rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Table created successfully\n");
    }

    char username[256];
    printf("Enter username: ");
    scanf("%255s", username);

    char password_hash[256];
    hash_password(PASSWORD, password_hash);

    char sql_insert[512];
    snprintf(sql_insert, sizeof(sql_insert), "INSERT INTO users (username, password_hash) VALUES ('%s', '%s');", username, password_hash);

    rc = sqlite3_exec(db, sql_insert, callback, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("User inserted successfully\n");
    }

    sqlite3_close(db);
    return 0;
}