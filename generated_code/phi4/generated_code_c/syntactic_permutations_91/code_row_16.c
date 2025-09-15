#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#define HASH_SIZE 32

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md = EVP_sha256();

    if (EVP_DigestInit_ex(ctx, md, NULL)) {
        EVP_DigestUpdate(ctx, password, strlen(password));
        unsigned int length;
        EVP_DigestFinal_ex(ctx, output, &length);
    }

    EVP_MD_CTX_free(ctx);
}

void register_user(const char *username, const char *password) {
    MYSQL *conn = mysql_init(NULL);

    if (conn == NULL || !mysql_real_connect(conn, "localhost", "root", "password", "test_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    unsigned char hash[HASH_SIZE];
    memset(hash, 0, HASH_SIZE);

    if (!RAND_bytes(hash, sizeof(hash))) {
        fprintf(stderr, "Error generating random bytes for salt.\n");
        exit(1);
    }

    hash_password(password, hash);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%.*s')",
             username, HASH_SIZE, hash);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}
