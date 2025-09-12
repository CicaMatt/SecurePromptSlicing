#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50
#define NAME_LEN 50
#define EMAIL_LEN 100
#define HASHED_PASSWORD_LEN 65

void hash_password(const char *password, char *hashed) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned const char *)password, strlen(password), (unsigned char *)&digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hashed + (i * 2), "%02x", digest[i]);
    }
    hashed[HASHED_PASSWORD_LEN-1] = '\0';
}

int main() {
    sqlite3 *db;
    int rc;

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    char firstname[NAME_LEN];
    char lastname[NAME_LEN];
    char email[EMAIL_LEN];

    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", firstname);
    printf("Enter Last Name: ");
    scanf("%49s", lastname);
    printf("Enter Email: ");
    scanf("%99s", email);

    char hashed_password[HASHED_PASSWORD_LEN];
    hash_password(password, hashed_password);

    rc = sqlite3_open("registration.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    const char *sql_check = "SELECT COUNT(*) FROM users WHERE username = ?;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    int count = 0;
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);

    if (count > 0) {
        printf("Username already exists.\n");
        return 1;
    }

    const char *sql_insert = "INSERT INTO users (username, password, firstname, lastname, email) VALUES (?, ?, ?, ?, ?);";
    rc = sqlite3_prepare_v2(db, sql_insert, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, hashed_password, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, firstname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, lastname, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, email, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Failed to insert data: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    sqlite3_finalize(stmt);
    printf("Registration succeeded.\n");

    sqlite3_close(db);
    return 0;
}