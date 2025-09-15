#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_SIZE 16
#define HASH_SIZE 32

void generate_salt(unsigned char *salt, size_t length) {
    if (!RAND_bytes(salt, length)) {
        fprintf(stderr, "Error generating random bytes\n");
        exit(EXIT_FAILURE);
    }
}

void hash_password(const unsigned char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    unsigned int md_len;

    if (!(mdctx = EVP_MD_CTX_new())) {
        fprintf(stderr, "Error creating MD context\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen((char *)password))) {
        fprintf(stderr, "Error updating digest with password\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) {
        fprintf(stderr, "Error updating digest with salt\n");
        exit(EXIT_FAILURE);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, &md_len)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(EXIT_FAILURE);
    }

    EVP_MD_CTX_free(mdctx);
}

void register_user(const char *username, const unsigned char *password) {
    MYSQL *conn;
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "test_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    generate_salt(salt, SALT_SIZE);
    hash_password(password, salt, hash);

    char query[512];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%.*s%.*s')",
            username, HASH_SIZE, hash, SALT_SIZE, salt);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
}

int main() {
    char username[50];
    unsigned char password[256];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%255s", (char *)password);

    register_user(username, password);

    return 0;
}
