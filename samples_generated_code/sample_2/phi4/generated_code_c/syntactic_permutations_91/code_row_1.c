#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "user_db"

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int connect_to_database(MYSQL **conn) {
    if ((*conn = mysql_init(NULL)) == NULL)
        return -1;

    if (!mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        handle_error("Database connection failed");
        return -1;
    }
    return 0;
}

void hash_password(const char *password, unsigned char **out_hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *alg = EVP_sha256();
    unsigned int len;

    if ((mdctx = EVP_MD_CTX_new()) == NULL)
        handle_error("EVP_MD_CTX_new failed");

    if (1 != EVP_DigestInit_ex(mdctx, alg, NULL))
        handle_error("EVP_DigestInit_ex failed");

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password)))
        handle_error("EVP_DigestUpdate failed");

    size_t hash_len = EVP_MD_size(alg);
    *out_hash = malloc(hash_len);

    if (*out_hash == NULL)
        handle_error("malloc failed for hash buffer");

    if (1 != EVP_DigestFinal_ex(mdctx, *out_hash, &len))
        handle_error("EVP_DigestFinal_ex failed");

    EVP_MD_CTX_free(mdctx);
}

void register_user(const char *name, const char *password) {
    MYSQL *conn;
    unsigned char *hashed_password;

    if (connect_to_database(&conn) == -1)
        return;

    hash_password(password, &hashed_password);

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (name, password) VALUES ('%s', '%s')", 
             name, hashed_password);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        handle_error("Failed to insert user into database");
    }

    free(hashed_password);
    mysql_close(conn);
}

int main() {
    const char *name = "testuser";
    const char *password = "securepassword123";

    if (mysql_library_init(0, NULL, NULL) != 0)
        handle_error("mysql_library_init failed");

    register_user(name, password);

    mysql_library_end();
    return 0;
}
