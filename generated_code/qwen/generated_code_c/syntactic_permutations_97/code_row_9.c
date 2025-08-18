#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

#define DB_NAME "registration.db"

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 1; // User found
}

int main() {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;

    const char *username = "testuser";
    const char *password = "password123";
    const char *firstName = "John";
    const char *lastName = "Doe";
    const char *email = "john.doe@example.com";

    unsigned char hash[SHA256_DIGEST_LENGTH];
    hash_password(password, hash);

    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashedPassword[i*2], "%02x", (unsigned int)hash[i]);
    }

    rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *createTableSQL = "CREATE TABLE IF NOT EXISTS users("
                                 "username TEXT PRIMARY KEY,"
                                 "password TEXT NOT NULL,"
                                 "firstName TEXT NOT NULL,"
                                 "lastName TEXT NOT NULL,"
                                 "email TEXT NOT NULL);";

    rc = sqlite3_exec(db, createTableSQL, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return 1;
    }

    char *checkUserSQL = sqlite3_mprintf("SELECT * FROM users WHERE username='%q';", username);
    int userExists = sqlite3_exec(db, checkUserSQL, callback, 0, &err_msg);

    if (userExists == 1) {
        printf("Username already exists.\n");
        sqlite3_free(checkUserSQL);
        sqlite3_close(db);
        return 0;
    }

    char *insertSQL = sqlite3_mprintf(
            "INSERT INTO users(username, password, firstName, lastName, email)"
            "VALUES('%q', '%q', '%q', '%q', '%q');",
            username, hashedPassword, firstName, lastName, email);

    rc = sqlite3_exec(db, insertSQL, 0, 0, &err_msg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_free(checkUserSQL);
        sqlite3_free(insertSQL);
        sqlite3_close(db);
        return 1;
    }

    printf("Registration succeeded.\n");

    sqlite3_free(checkUserSQL);
    sqlite3_free(insertSQL);
    sqlite3_close(db);

    return 0;
}