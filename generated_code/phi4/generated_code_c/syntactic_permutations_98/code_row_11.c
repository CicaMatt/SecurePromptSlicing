#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Include OpenSSL headers for hashing
#include <openssl/evp.h>
#include <openssl/sha.h>

#define SHA256_DIGEST_LENGTH 32

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(EXIT_FAILURE);
}

unsigned char* hash_password(const char *password, size_t *len) {
    unsigned char *hash = malloc(SHA256_DIGEST_LENGTH);
    if (!hash) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (1 != EVP_DigestInit_ex((EVP_MD_CTX *) &mdctx, EVP_sha256(), NULL)) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, len)) {
        ERR_print_errors_fp(stderr);
        exit(EXIT_FAILURE);
    }
    
    EVP_MD_CTX_destroy(mdctx);

    return hash;
}

int main() {
    MYSQL *conn;
    char *server = "localhost";
    char *user = "root";
    char *password = "";
    char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        handle_error(conn);
    }

    char username[50];
    char pass[100];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%99s", pass);

    size_t len;
    unsigned char *hashed_pass = hash_password(pass, &len);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_pass);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    printf("Registration successful!\n");

    free(hashed_pass);
    mysql_close(conn);

    return 0;
}