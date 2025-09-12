#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sqlite3.h>

#define SALT_SIZE 8
#define HASH_SIZE SHA256_DIGEST_LENGTH

void generate_salt(char *salt, size_t salt_size) {
    FILE *urandom = fopen("/dev/urandom", "rb");
    fread(salt, 1, salt_size - 1, urandom);
    fclose(urandom);
    salt[salt_size - 1] = '\0';
}

void hash_password(const char *password, const char *salt, unsigned char *output) {
    unsigned char combined[128];
    snprintf((char *)combined, sizeof(combined), "%s%s", password, salt);
    SHA256(combined, strlen((const char *)combined), output);
}

int main() {
    char username[100], password[100];
    char salt[SALT_SIZE + 1];
    unsigned char hashed_password[HASH_SIZE + 1];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    generate_salt(salt, SALT_SIZE + 1);
    hash_password(password, salt, hashed_password);
    char salt_hex[SALT_SIZE * 2 + 1];
    for (int i = 0; i < SALT_SIZE; i++) {
        sprintf(&salt_hex[i * 2], "%02x", (unsigned int)salt[i]);
    }
    char hash_hex[HASH_SIZE * 2 + 1];
    for (int i = 0; i < HASH_SIZE; i++) {
        sprintf(&hash_hex[i * 2], "%02x", (unsigned int)hashed_password[i]);
    }

    sqlite3 *db;
    if (sqlite3_open("users.db", &db)) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    const char *sql = "CREATE TABLE IF NOT EXISTS users (username TEXT, salt TEXT, hash TEXT);";
    sqlite3_exec(db, sql, NULL, NULL, NULL);

    char insert_sql[512];
    snprintf(insert_sql, sizeof(insert_sql), 
             "INSERT INTO users (username, salt, hash) VALUES ('%s', '%s', '%s');", 
             username, salt_hex, hash_hex);
    
    if (sqlite3_exec(db, insert_sql, NULL, NULL, NULL)) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    sqlite3_close(db);

    printf("User registered successfully.\n");
    return 0;
}