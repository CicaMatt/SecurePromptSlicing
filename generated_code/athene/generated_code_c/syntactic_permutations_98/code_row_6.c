#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

int hash_password(const char *password, unsigned char *output) {
    SHA1((unsigned char*)password, strlen(password), output);
    return 0;
}

int insert_into_db(sqlite3 *db, const char *username, const unsigned char *hashed_password) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO users (username, password_hash) VALUES ('%s', X'%s')", 
             username, sqlite3_mprintf("%x", hashed_password, SHA_DIGEST_LENGTH));
    
    char *err_msg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        return -1;
    }
    return 0;
}

int main() {
    const char *username = "testuser";
    const char *password = "securepassword";

    unsigned char hashed_password[SHA_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    sqlite3 *db;
    int rc = sqlite3_open("example.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, password_hash BLOB)";
    char *err_msg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return -1;
    }

    rc = insert_into_db(db, username, hashed_password);
    if (rc != 0) {
        sqlite3_close(db);
        return -1;
    }

    sqlite3_close(db);
    return 0;
}