#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 100
#define HASH_LENGTH SHA256_DIGEST_LENGTH

void hash_password(const char *password, unsigned char *hash) {
    SHA256_CTX sha_ctx;
    SHA256_Init(&sha_ctx);
    SHA256_Update(&sha_ctx, password, strlen(password));
    SHA256_Final(hash, &sha_ctx);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char hash[HASH_LENGTH];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    hash_password(password, hash);

    char hash_str[(HASH_LENGTH * 2) + 1];
    for (int i = 0; i < HASH_LENGTH; ++i) {
        sprintf(&hash_str[i*2], "%02x", (unsigned int)hash[i]);
    }

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')", username, hash_str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return 0;
}