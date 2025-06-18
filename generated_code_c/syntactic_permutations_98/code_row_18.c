#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

typedef struct {
    char username[20];
    char password[30];
} user_t;

int insert_user(const char* username, const char* password) {
    // hash the password
    unsigned char hashed_password[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)password, strlen(password), hashed_password);

    // insert the user into the database
    const char* query = "INSERT INTO users (username, password) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, hashed_password, SHA_DIGEST_LENGTH, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert user: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    return 0;
}