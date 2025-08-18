#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <sqlite3.h>

#define SALT_SIZE 16

void handleErrors(void) {
    ERR_print_errors_fp(stderr);
    abort();
}

int createSalt(unsigned char *salt, size_t salt_len) {
    if (RAND_bytes(salt, salt_len) != 1) {
        return -1;
    }
    return 0;
}

int hashPassword(const unsigned char *password, const unsigned char *salt, unsigned char **hash, size_t *hash_len) {
    EVP_MD_CTX *mdctx = NULL;
    const EVP_MD *alg_nid = EVP_sha256();
    int success = -1;

    if (EVP_MD_size(alg_nid) <= 0)
        goto done;

    mdctx = EVP_MD_CTX_new();
    if (!mdctx)
        goto done;

    if (1 != EVP_DigestInit_ex(mdctx, alg_nid, NULL))
        goto done;

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE))
        goto done;

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password)))
        goto done;

    *hash_len = EVP_MD_size(alg_nid);
    *hash = malloc(*hash_len);

    if (*hash == NULL)
        goto done;

    if (1 != EVP_DigestFinal_ex(mdctx, *hash, hash_len))
        goto done;

    success = 0;
done:
    EVP_MD_CTX_destroy(mdctx);
    return success;
}

int insertCredentials(sqlite3 *db, const char *username, const unsigned char *salt, const unsigned char *hashed_password) {
    sqlite3_stmt *stmt;
    const char *insert_sql =
        "INSERT INTO users (username, salt, hashed_password) VALUES (?, ?, ?);";

    if (sqlite3_prepare_v2(db, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    if (sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_blob(stmt, 2, salt, SALT_SIZE, SQLITE_STATIC) != SQLITE_OK ||
        sqlite3_bind_blob(stmt, 3, hashed_password, EVP_MD_size(EVP_sha256()), SQLITE_STATIC) != SQLITE_OK) {
        fprintf(stderr, "Failed to bind parameters: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return 0;
}

int main() {
    const char *db_name = "credentials.db";
    sqlite3 *db;
    if (sqlite3_open(db_name, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return EXIT_FAILURE;
    }

    char create_table_sql[] =
        "CREATE TABLE IF NOT EXISTS users ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
            "username TEXT UNIQUE NOT NULL, "
            "salt BLOB NOT NULL, "
            "hashed_password BLOB NOT NULL);";

    if (sqlite3_exec(db, create_table_sql, 0, 0, 0) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    char username[256];
    printf("Enter username: ");
    scanf("%255s", username);

    unsigned char password[256];
    printf("Enter password: ");
    scanf("%255s", (char *)password);

    unsigned char salt[SALT_SIZE];
    if (createSalt(salt, SALT_SIZE) != 0) {
        handleErrors();
    }

    unsigned char *hashed_password;
    size_t hash_len;
    if (hashPassword(password, salt, &hashed_password, &hash_len) != 0) {
        handleErrors();
    }

    if (insertCredentials(db, username, salt, hashed_password) != 0) {
        fprintf(stderr, "Failed to insert credentials.\n");
        free(hashed_password);
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    printf("Credentials inserted successfully.\n");

    free(hashed_password);
    sqlite3_close(db);

    return EXIT_SUCCESS;
}