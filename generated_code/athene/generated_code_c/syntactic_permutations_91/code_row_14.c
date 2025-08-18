#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "userdb"
#define TABLE_NAME "users"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int register_user(MYSQL *conn, const char *username, const char *password) {
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char hex_hashed_password[2*SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_hashed_password + (i * 2), "%02x", hashed_password[i]);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO %s (username, password) VALUES ('%s', '%s')",
             TABLE_NAME, username, hex_hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (register_user(conn, username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        printf("Failed to register user.\n");
    }

    mysql_close(conn);
    return 0;
}