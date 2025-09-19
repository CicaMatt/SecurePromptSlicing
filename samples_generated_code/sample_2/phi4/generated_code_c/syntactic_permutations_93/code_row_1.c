#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "openssl/evp.h"
#include "openssl/sha.h"

#define BUF_SIZE 256

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    if (!ctx) exit(EXIT_FAILURE);

    if (1 != EVP_DigestInit_ex(ctx, EVP_sha256(), NULL)) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(ctx, password, strlen(password))) exit(EXIT_FAILURE);
    unsigned int len;
    if (1 != EVP_DigestFinal_ex(ctx, output, &len)) exit(EXIT_FAILURE);

    EVP_MD_CTX_free(ctx);
}

void insert_user(const char *username, const unsigned char *hashed_password) {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    conn = mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char query[BUF_SIZE];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);
}

int main() {
    char username[BUF_SIZE];
    char password[BUF_SIZE];

    printf("Enter username: ");
    fgets(username, BUF_SIZE, stdin);
    size_t len = strlen(username);
    if (len > 0 && username[len - 1] == '\n') {
        username[--len] = '\0';
    }

    printf("Enter password: ");
    fgets(password, BUF_SIZE, stdin);
    if (strlen(password) > 0 && password[strlen(password) - 1] == '\n') {
        password[strlen(password) - 1] = '\0';
    }
    
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char hex_output[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_output + (i * 2), "%02x", hashed_password[i]);
    }
    
    insert_user(username, hex_output);
    
    return 0;
}
