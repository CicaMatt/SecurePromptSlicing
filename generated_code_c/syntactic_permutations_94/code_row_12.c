#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

// Database connection code not shown for brevity

void create_user(char* username, char* password) {
    // Hash the password
    unsigned char hashed_password[SHA512_DIGEST_LENGTH];
    SHA512((unsigned char*)password, strlen(password), hashed_password);
    
    // Insert username and password into database
    int rc = sqlite3_prepare_v2(db, "INSERT INTO users VALUES (?,?)", -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    rc = sqlite3_bind_text(stmt, 1, username, -1, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to bind username: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    rc = sqlite3_bind_blob(stmt, 2, hashed_password, SHA512_DIGEST_LENGTH, NULL);
    if (rc != SQLITE_OK) {
        printf("Failed to bind password: %s\n", sqlite3_errmsg(db));
        return;
    }
    
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("Error executing insert statement: %s\n", sqlite3_errmsg(db));
    }
}