#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_SIZE 16

void hash_password(const char *password, unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();

    if (!(mdctx = EVP_MD_CTX_create())) {
        fprintf(stderr, "EVP_MD_CTX_create failed\n");
        exit(1);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "EVP_DigestInit_ex failed\n");
        exit(1);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "EVP_DigestUpdate with salt failed\n");
        exit(1);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        fprintf(stderr, "EVP_DigestUpdate with password failed\n");
        exit(1);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, NULL)) {
        fprintf(stderr, "EVP_DigestFinal_ex failed\n");
        exit(1);
    }

    EVP_MD_CTX_destroy(mdctx);
}

void generate_salt(unsigned char *salt) {
    if (!RAND_bytes(salt, SALT_SIZE)) {
        fprintf(stderr, "RAND_bytes failed\n");
        exit(1);
    }
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; // Change to your MySQL password
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    unsigned char salt[SALT_SIZE];
    unsigned char hash[EVP_MAX_MD_SIZE];

    generate_salt(salt);

    char input_password[256];
    printf("Enter username: ");
    char username[128];
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", input_password);

    hash_password(input_password, salt, hash);

    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%s', '%s')",
             username,
             mysql_real_escape_string(conn, (char *)hash, EVP_MAX_MD_SIZE),
             mysql_real_escape_string(conn, (char *)salt, SALT_SIZE));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);

    return 0;
}