#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <sqlite3.h>

#define SALT "fixed_salt_value"
#define DB_FILE "users.db"

void hash_password(const char *password, unsigned char **hashed) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned int md_len;

    if (!(md = EVP_get_digestbyname("sha256"))) {
        fprintf(stderr, "Unknown message digest\n");
        exit(1);
    }

    mdctx = EVP_MD_CTX_create();
    EVP_DigestInit_ex(mdctx, md, NULL);

    const char *salted_password = strcat(SALT, password);
    EVP_DigestUpdate(mdctx, salted_password, strlen(salted_password));
    
    unsigned char md_value[EVP_MAX_MD_SIZE];
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    *hashed = (unsigned char *)malloc(md_len);

    memcpy(*hashed, md_value, md_len);
    EVP_MD_CTX_destroy(mdctx);
}

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void create_table(sqlite3 *db) {
    char *err_msg = NULL;

    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "username TEXT NOT NULL UNIQUE, "
        "password_hash TEXT NOT NULL);";

    if (sqlite3_exec(db, sql, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

void insert_user(sqlite3 *db, const char *username, unsigned char *hashed_password) {
    char sql[256];
    sprintf(sql, "INSERT INTO users (username, password_hash) VALUES ('%s', X'%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x');",
            username,
            hashed_password[0], hashed_password[1],
            hashed_password[2], hashed_password[3],
            hashed_password[4], hashed_password[5],
            hashed_password[6], hashed_password[7],
            hashed_password[8], hashed_password[9],
            hashed_password[10], hashed_password[11],
            hashed_password[12], hashed_password[13],
            hashed_password[14], hashed_password[15]);

    char *err_msg = NULL;
    if (sqlite3_exec(db, sql, callback, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
}

int main() {
    const char *username;
    char password[256];
    
    printf("Enter username: ");
    scanf("%ms", &username);

    printf("Enter password: ");
    scanf("%255s", password);

    unsigned char *hashed_password = NULL;
    hash_password(password, &hashed_password);

    sqlite3 *db;
    if (sqlite3_open(DB_FILE, &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    create_table(db);
    insert_user(db, username, hashed_password);

    sqlite3_close(db);
    
    free(hashed_password);
    free(username);

    return 0;
}