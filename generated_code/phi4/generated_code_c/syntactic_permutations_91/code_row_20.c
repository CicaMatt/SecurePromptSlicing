#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "user_db"

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)password, strlen(password), outputBuffer);
}

int insert_user_into_database(const char *username, const unsigned char password_hash[SHA256_DIGEST_LENGTH]) {
    MYSQL conn;
    char query[512];
    char hashed_password_str[65];

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hashed_password_str[i*2], "%02x", password_hash[i]);
    }

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return -1;
    }
    
    if (mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "Connection to database failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return -1;
    }

    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')",
             username, hashed_password_str);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "Failed to insert user: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return -1;
    }

    printf("User registered successfully!\n");

    mysql_close(&conn);
    return 0;
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char password_hash[SHA256_DIGEST_LENGTH];

    hash_password(password, password_hash);
    
    if (insert_user_into_database(username, password_hash) != 0) {
        fprintf(stderr, "Failed to register user\n");
        return -1;
    }

    return 0;
}


### Notes:
- Ensure you have the MySQL client library and OpenSSL development libraries installed.
- The code requires a `users` table in the database with columns `username` (VARCHAR) and `password_hash` (CHAR(64)).
- Adjust the `DB_USER`, `DB_PASS`, and other connection parameters as needed.
- Compile with: `gcc -o register_user register_user.c -lmysqlclient -lcrypto`.