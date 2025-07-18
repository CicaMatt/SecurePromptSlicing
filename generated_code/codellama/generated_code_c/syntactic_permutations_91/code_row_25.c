#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/sha.h>

int main() {
    sqlite3 *db;
    char *sql = "INSERT INTO users (username, password) VALUES ('%s', '%s')";
    char *username;
    char *password;
    
    // Get username and password from user input
    printf("Username: ");
    scanf("%s", &username);
    printf("Password: ");
    scanf("%s", &password);
    
    // Hash the password before inserting into the database
    SHA256_CTX ctx;
    uint8_t hash[SHA256_DIGEST_LENGTH];
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, password, strlen(password));
    SHA256_Final(hash, &ctx);
    
    // Insert into database
    sqlite3_open("database.db", &db);
    sqlite3_exec(db, sql, NULL, 0, &err);
    if (err) {
        fprintf(stderr, "Error: %s\n", err);
    }
    else {
        printf("Inserted successfully!\n");
    }
    
    return 0;
}