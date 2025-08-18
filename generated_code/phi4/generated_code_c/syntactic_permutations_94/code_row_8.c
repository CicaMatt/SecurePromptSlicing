#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void hash_password(const char *password, unsigned char salt[SALT_SIZE], unsigned char hash[HASH_SIZE]) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) exit(EXIT_FAILURE);

    if (1 != EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(ctx, salt, SALT_SIZE)) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(ctx, password, strlen(password))) exit(EXIT_FAILURE);
    if (1 != EVP_DigestFinal_ex(ctx, hash, NULL)) exit(EXIT_FAILURE);

    EVP_MD_CTX_free(ctx);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char username[256];
    char password[256];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    unsigned char salt[SALT_SIZE];
    if (1 != RAND_bytes(salt, SALT_SIZE)) {
        fprintf(stderr, "Error generating salt\n");
        return EXIT_FAILURE;
    }

    unsigned char hash[HASH_SIZE];
    hash_password(password, salt, hash);

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%.*s', '%.*s')", 
             username,
             HASH_SIZE * 2, hash,
             SALT_SIZE * 2, salt);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return EXIT_SUCCESS;
}