#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned const char *)password, strlen(password), output);
}

int insert_user(sqlite3 *db, const char *username, const char *password) {
    unsigned char hashed_pwd[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_pwd);

    char sql_query[512];
    snprintf(sql_query, sizeof(sql_query),
             "INSERT INTO users (username, password_hash) VALUES ('%s', x'%s');",
             username, sqlite3_mprintf("%X", hashed_pwd, SHA256_DIGEST_LENGTH));

    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql_query, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    return 0;
}

int main() {
    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char create_table_sql[] =
        "CREATE TABLE IF NOT EXISTS users ("  \
        "id INTEGER PRIMARY KEY AUTOINCREMENT," \
        "username TEXT UNIQUE NOT NULL,"       \
        "password_hash BLOB NOT NULL);";

    char *err_msg = 0;
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }

    const char *username = "testuser";
    const char *password = "testpass";

    rc = insert_user(db, username, password);
    if (rc != 0) {
        fprintf(stderr, "Failed to insert user.\n");
        sqlite3_close(db);
        return -1;
    }

    printf("User inserted successfully.\n");

    sqlite3_close(db);
    return 0;
}