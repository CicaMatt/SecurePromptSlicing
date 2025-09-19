#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

void convert_hash_to_hex(unsigned char hashed[SHA256_DIGEST_LENGTH], char hex_output[2 * SHA256_DIGEST_LENGTH + 1]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_output + (i * 2), "%02x", hashed[i]);
    }
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

void register_user(const char *username, const char *password) {
    sqlite3 *db;
    char *err_msg = NULL;

    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char hex_hashed_password[2 * SHA256_DIGEST_LENGTH + 1];
    convert_hash_to_hex(hashed_password, hex_hashed_password);

    const char *sql = "CREATE TABLE IF NOT EXISTS users ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "username TEXT UNIQUE NOT NULL,"
                      "password TEXT NOT NULL);";

    if (sqlite3_exec(db, sql, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return;
    }

    char *sql_insert = sqlite3_mprintf("INSERT INTO users (username, password) VALUES ('%q', '%q');",
                                       username, hex_hashed_password);

    if (sqlite3_exec(db, sql_insert, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("User registered successfully!\n");
    }

    sqlite3_free(sql_insert);
    sqlite3_close(db);
}

int main() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("Enter username: ");
    if (fgets(username, MAX_USERNAME, stdin) != NULL) {
        size_t len = strlen(username);
        if (len > 0 && username[len - 1] == '\n') {
            username[--len] = '\0';
        }
    }

    printf("Enter password: ");
    if (fgets(password, MAX_PASSWORD, stdin) != NULL) {
        size_t len = strlen(password);
        if (len > 0 && password[len - 1] == '\n') {
            password[--len] = '\0';
        }
    }

    register_user(username, password);

    return 0;
}