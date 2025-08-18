#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT "mysecretsalt"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

void hash_password(const char *password, unsigned char *hashed_password) {
    char salted_password[MAX_PASSWORD_LENGTH + strlen(SALT)];
    strcpy(salted_password, password);
    strcat(salted_password, SALT);

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, salted_password, strlen(salted_password));
    SHA256_Final(hashed_password, &sha256);
}

int insert_user_into_db(const char *username, const unsigned char *hashed_password) {
    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql_create_table = "CREATE TABLE IF NOT EXISTS users("
                                   "username TEXT PRIMARY KEY,"
                                   "password BLOB);";

    rc = sqlite3_exec(db, sql_create_table, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    char sql_insert[256];
    snprintf(sql_insert, sizeof(sql_insert), 
             "INSERT INTO users (username, password) VALUES ('%q', x'%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x');", 
             username,
             hashed_password[0],  hashed_password[1],  hashed_password[2],  hashed_password[3],
             hashed_password[4],  hashed_password[5],  hashed_password[6],  hashed_password[7],
             hashed_password[8],  hashed_password[9],  hashed_password[10], hashed_password[11],
             hashed_password[12], hashed_password[13], hashed_password[14], hashed_password[15],
             hashed_password[16], hashed_password[17], hashed_password[18], hashed_password[19],
             hashed_password[20], hashed_password[21], hashed_password[22], hashed_password[23],
             hashed_password[24], hashed_password[25], hashed_password[26], hashed_password[27],
             hashed_password[28], hashed_password[29], hashed_password[30], hashed_password[31]);

    rc = sqlite3_exec(db, sql_insert, 0, 0, &err_message);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    }

    sqlite3_close(db);
    return rc;
}

int main() {
    char username[MAX_USERNAME_LENGTH + 1];
    char password[MAX_PASSWORD_LENGTH + 1];

    printf("Enter username: ");
    scanf("%50s", username);

    printf("Enter password: ");
    scanf("%50s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    if (insert_user_into_db(username, hashed_password) == SQLITE_OK) {
        printf("User inserted successfully.\n");
    } else {
        printf("Failed to insert user.\n");
    }

    return 0;
}