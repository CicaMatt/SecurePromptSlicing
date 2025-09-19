#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define BUF_SIZE 256

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

unsigned char* sha256_hash(const unsigned char* data, size_t len, unsigned char** hash_len) {
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) handle_error("EVP_MD_CTX_new failed");

    const EVP_MD* md = EVP_sha256();
    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) handle_error("DigestInitEx failed");
    if (1 != EVP_DigestUpdate(mdctx, data, len)) handle_error("DigestUpdate failed");
    unsigned char hash[EVP_MAX_MD_SIZE];
    if (1 != EVP_DigestFinal_ex(mdctx, hash, hash_len)) handle_error("DigestFinalEx failed");

    EVP_MD_CTX_free(mdctx);
    unsigned char* hashed_data = malloc(BUF_SIZE);
    for (int i = 0; i < *hash_len; i++) {
        sprintf((char*)&hashed_data[i * 2], "%02x", hash[i]);
    }
    return hashed_data;
}

void register_user(MYSQL* conn, const char* name, const char* password) {
    unsigned char* hashed_password = NULL;
    unsigned char* hash_len = malloc(sizeof(unsigned int));
    
    hashed_password = sha256_hash((const unsigned char*)password, strlen(password), &hash_len);
    
    char query[BUF_SIZE];
    snprintf(query, BUF_SIZE, "INSERT INTO users (name, password) VALUES ('%s', '%s')", name, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(hashed_password);
        exit(EXIT_FAILURE);
    }

    free(hashed_password);
    free(hash_len);
}

int main() {
    MYSQL* conn;
    conn = mysql_init(NULL);
    
    if (!conn) handle_error("mysql_init failed");

    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    char name[BUF_SIZE];
    char password[BUF_SIZE];

    printf("Enter name: ");
    scanf("%255s", name);

    printf("Enter password: ");
    scanf("%255s", password);

    register_user(conn, name, password);

    mysql_close(conn);
    return 0;
}