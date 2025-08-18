#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 128
#define SALT_LENGTH 16

void generateSalt(unsigned char *salt) {
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(salt, sizeof(unsigned char), SALT_LENGTH, urandom);
    fclose(urandom);
}

char* hashPassword(const char *password, const unsigned char *salt) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    SHA256_Update(&sha256, salt, SALT_LENGTH);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    static char hashString[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashString[i * 2], "%02x", hash[i]);
    }

    return hashString;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   for (int i = 0; i < argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void registerUser(sqlite3 *db, const char *username, const char *password) {
    unsigned char salt[SALT_LENGTH];
    generateSalt(salt);

    char saltHex[SALT_LENGTH * 2 + 1];
    for (int i = 0; i < SALT_LENGTH; i++) {
        sprintf(&saltHex[i * 2], "%02x", salt[i]);
    }

    const char *hashedPassword = hashPassword(password, salt);
    char sql[512];
    snprintf(sql, sizeof(sql),
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%s', '%s');",
             username, hashedPassword, saltHex);

    sqlite3_exec(db, sql, callback, 0, 0);
}

int main() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter Username: ");
    scanf("%50s", username);
    printf("Enter Password: ");
    scanf("%128s", password);

    sqlite3 *db;
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    const char *sqlCreateTable = 
        "CREATE TABLE IF NOT EXISTS users("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "username TEXT NOT NULL UNIQUE,"
        "password_hash TEXT NOT NULL,"
        "salt TEXT NOT NULL);";

    sqlite3_exec(db, sqlCreateTable, callback, 0, 0);

    registerUser(db, username, password);
    printf("User registered successfully.\n");

    sqlite3_close(db);
    return 0;
}