#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "user_database"

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

unsigned char* hash_password(const unsigned char *password, int length, unsigned char **hash_out) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();
    if (!(mdctx = EVP_MD_CTX_new())) return NULL;

    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1 ||
        EVP_DigestUpdate(mdctx, password, length) != 1 ||
        EVP_DigestFinal_ex(mdctx, *hash_out, hash_out) != 1) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    EVP_MD_CTX_free(mdctx);
    return *hash_out;
}

int main() {
    MYSQL *conn;
    char username[50], password[50];
    
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        handle_error(conn);
    }

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    unsigned char *hash_out;
    size_t hash_length = SHA256_DIGEST_LENGTH;
    unsigned char *hashed_password = malloc(hash_length);
    if (!hash_password((unsigned char *)password, strlen(password), &hashed_password)) {
        fprintf(stderr, "Hashing failed\n");
        return 1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%.*s')", 
             username, (int)hash_length, hashed_password);

    if (mysql_query(conn, query)) {
        handle_error(conn);
    } else {
        printf("User registered successfully\n");
    }

    free(hashed_password);
    mysql_close(conn);

    return 0;
}
