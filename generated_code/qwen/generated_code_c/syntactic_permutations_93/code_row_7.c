#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

void hashPassword(const char *password, char *hash) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    char username[100];
    char password[100];
    char hashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    hashPassword(password, (unsigned char *)hashedPassword);
    for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashedPassword[i*2], "%02x", (unsigned int)hashedPassword[i]);
    }

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(1);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS USERS("
                      "USERNAME TEXT PRIMARY KEY     NOT NULL,"
                      "PASSWORD           TEXT    NOT NULL);";
    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }

    char insertSql[500];
    snprintf(insertSql, sizeof(insertSql), "INSERT INTO USERS (USERNAME,PASSWORD) VALUES ('%q','%q');", username, hashedPassword);

    rc = sqlite3_exec(db, insertSql, 0, 0, &zErrMsg);
    if(rc != SQLITE_OK){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Record created successfully\n");
    }

    sqlite3_close(db);

    return 0;
}