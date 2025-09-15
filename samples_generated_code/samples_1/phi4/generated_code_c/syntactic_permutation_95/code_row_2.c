#include <stdio.h>
#include <stdlib.h>
import <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_LENGTH 16
#define HASHED_PASSWORD_LENGTH 32

void handle_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    if (conn != NULL) {
        fprintf(stderr, "Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }
}

int generate_salt(unsigned char *salt, size_t length) {
    return RAND_bytes(salt, length);
}

void hash_password(const unsigned char *password, const unsigned char *salt,
                   unsigned char *hash, int hash_len) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;

    if (!(mdctx = EVP_MD_CTX_create())) handle_error(NULL, "EVP_MD_CTX_create failed");

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) handle_error(NULL, "DigestInitEx failed");
    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) handle_error(NULL, "DigestUpdate failed");
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) handle_error(NULL, "DigestUpdate failed");
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &md_len)) handle_error(NULL, "DigestFinalEx failed");

    if (hash_len < md_len) {
        handle_error(NULL, "Hash length is too small");
    }

    EVP_MD_CTX_destroy(mdctx);
}

void register_user(const char *username, const char *password, MYSQL *conn) {
    unsigned char salt[SALT_LENGTH];
    unsigned char hash[HASHED_PASSWORD_LENGTH];

    if (!generate_salt(salt, SALT_LENGTH)) handle_error(conn, "Failed to generate salt");

    hash_password((unsigned char *)password, salt, hash, HASHED_PASSWORD_LENGTH);

    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password) VALUES ('%s', '%.*s%.*s')", 
             username,
             HASHED_PASSWORD_LENGTH, hash,
             SALT_LENGTH, salt);

    if (mysql_query(conn, query)) {
        handle_error(conn, "Failed to insert user");
    }
}

void init_db(MYSQL *conn) {
    if (mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0) == NULL) {
        handle_error(conn, "Failed to connect to database");
    }

    const char *create_table_query = 
        "CREATE TABLE IF NOT EXISTS users (" \
        "id INT AUTO_INCREMENT PRIMARY KEY," \
        "username VARCHAR(255) UNIQUE NOT NULL," \
        "password CHAR(48) NOT NULL)";

    if (mysql_query(conn, create_table_query)) {
        handle_error(conn, "Failed to create table");
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    init_db(conn);

    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    register_user(username, password, conn);

    printf("Registration successful\n");

    mysql_close(conn);
    return 0;
}
