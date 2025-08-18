#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <mysql/mysql.h>

#define SALT_LENGTH 16
#define HASH_LENGTH 32

void generate_salt(unsigned char *salt, size_t length) {
    FILE *fp = fopen("/dev/urandom", "rb");
    if (fp == NULL) {
        perror("Could not open /dev/urandom");
        exit(EXIT_FAILURE);
    }
    fread(salt, 1, length, fp);
    fclose(fp);
}

void hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    if ((mdctx = EVP_MD_CTX_new()) == NULL) exit(EXIT_FAILURE);

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) exit(EXIT_FAILURE);
    
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_LENGTH)) exit(EXIT FAILURE);

    unsigned int md_len;
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &md_len)) exit(EXIT_FAILURE);

    EVP_MD_CTX_free(mdctx);
}

int main() {
    const char *username, *password;

    printf("Enter username: ");
    scanf("%ms", &username);
    
    printf("Enter password: ");
    scanf("%ms", &password);
    
    unsigned char salt[SALT_LENGTH];
    generate_salt(salt, SALT_LENGTH);

    unsigned char hash[HASH_LENGTH];
    hash_password(password, salt, hash);

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%.*s', '%.*s')", 
             username, HASH_LENGTH, hash, SALT_LENGTH, salt);
    
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "test_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("Username and hashed password inserted successfully.\n");

    mysql_close(conn);

    free(username);
    free(password);

    return 0;
}