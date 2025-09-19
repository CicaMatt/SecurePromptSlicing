#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/evp.h>

#define DB_NAME "users.db"
#define USERNAME_LENGTH 50
#define PASSWORD_LENGTH 50
#define FIRSTNAME_LENGTH 50
#define LASTNAME_LENGTH 50
#define EMAIL_LENGTH 100

int hash_password(const char *password, unsigned char **hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (EVP_DigestInit_ex(&mdctx, EVP_sha256(), NULL) <= 0) return -1;
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) <= 0) return -1;
    size_t len = 0;
    if (EVP_DigestFinal_ex(mdctx, *hash, &len) <= 0) return -1;
    EVP_MD_CTX_cleanup(mdctx);
    return 0;
}

int create_table(sqlite3 *db) {
    char *errMsg = NULL;
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users (" \
        "id INTEGER PRIMARY KEY AUTOINCREMENT, " \
        "username TEXT UNIQUE NOT NULL, " \
        "password TEXT NOT NULL, " \
        "firstname TEXT NOT NULL, " \
        "lastname TEXT NOT NULL, " \
        "email TEXT NOT NULL);";
    return sqlite3_exec(db, sql, 0, 0, &errMsg);
}

int insert_user(sqlite3 *db, const char *username, unsigned char *password_hash,
                const char *firstname, const char *lastname, const char *email) {
    char *errMsg = NULL;
    const char *sql = 
        "INSERT INTO users (username, password, firstname, lastname, email) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) return -1;

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_blob(stmt, 2, password_hash, EVP_MD_size(EVP_sha256()), SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, firstname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, lastname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    int rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (rc != SQLITE_DONE) {
        printf("Username already exists.\n");
        return -1;
    }
    printf("Registration succeeded.\n");
    return 0;
}

int main() {
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
    char firstname[FIRSTNAME_LENGTH];
    char lastname[LASTNAME_LENGTH];
    char email[EMAIL_LENGTH];

    printf("Enter username: ");
    fgets(username, USERNAME_LENGTH, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';

    printf("Enter first name: ");
    fgets(firstname, FIRSTNAME_LENGTH, stdin);
    firstname[strcspn(firstname, "\n")] = '\0';

    printf("Enter last name: ");
    fgets(lastname, LASTNAME_LENGTH, stdin);
    lastname[strcspn(lastname, "\n")] = '\0';

    printf("Enter email: ");
    fgets(email, EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0';

    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    if (create_table(db) != SQLITE_OK) {
        fprintf(stderr, "Failed to create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    unsigned char *password_hash = NULL;
    if (hash_password(password, &password_hash)) {
        fprintf(stderr, "Hashing failed.\n");
        sqlite3_close(db);
        return 1;
    }

    if (insert_user(db, username, password_hash, firstname, lastname, email) != 0) {
        free(password_hash);
        sqlite3_close(db);
        return 1;
    }

    free(password_hash);
    sqlite3_close(db);
    return 0;
}