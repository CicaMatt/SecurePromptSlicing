#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "openssl/sha.h"
#include "sqlite3.h"

void create_table() {
    sqlite3 *db;
    char *error = 0;
    int rc = sqlite3_open("users.db", &db);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT, firstname TEXT, lastname TEXT, email TEXT)";
    
    rc = sqlite3_exec(db, sql, 0, 0, &error);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to create table\n");
    }
    
    sqlite3_close(db);
}

int check_username(const char *username) {
    int exists = 0;
    sqlite3 *db;
    char *error = 0;
    char *sql = "SELECT username FROM users WHERE username = ?";
    
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return exists;
    }
    
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username, -1, NULL);
        
        while (sqlite3_step(stmt) != SQLITE_DONE) {
            exists = 1;
        }
    } else {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    return exists;
}

void register_user(const char *username, const char *password, const char *firstname, const char *lastname, const char *email) {
    sqlite3 *db;
    char *error = 0;
    char sql[256];
    
    sprintf(sql, "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s')", username, password, firstname, lastname, email);
    
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Failed to open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }
    
    char *response = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &error);
    
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to insert data\n");
    } else {
        response = "Registration successfull";
    }
    
    sqlite3_free(error);
    sqlite3_close(db);
    
    printf("%s\n", response);
}

void hash_password(const char *password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
    
    int i = 0;
    char hash_string[SHA256_DIGEST_LENGTH * 2 + 1];
    for (i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hash_string[i*2], "%02x", hash[i]);
    }
    
    printf("%s\n", hash_string);
}

int main() {
    create_table();
    
    char username[32];
    char password[64];
    char firstname[64];
    char lastname[64];
    char email[128];
    
    printf("Enter username: ");
    scanf("%s", username);
    
    if (check_username(username)) {
        printf("Username already exists\n");
    } else {
        printf("Password: ");
        scanf("%s", password);
        
        hash_password(password);
        
        printf("First name: ");
        scanf("%s", firstname);
        
        printf("Last name: ");
        scanf("%s", lastname);
        
        printf("Email address: ");
        scanf("%s", email);
        
        register_user(username, password, firstname, lastname, email);
    }
    
    return 0;
}