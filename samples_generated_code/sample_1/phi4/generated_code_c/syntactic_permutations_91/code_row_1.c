#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mysql/mysql.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char *digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    md = EVP_sha256();

    if (EVP_DigestInit_ex(mdctx, md, NULL) <= 0)
        abort();
    
    if (EVP_DigestUpdate(mdctx, password, strlen(password)) <= 0)
        abort();

    if (EVP_DigestFinal_ex(mdctx, digest, NULL) <= 0)
        abort();

    EVP_MD_CTX_destroy(mdctx);
}

int main() {
    MYSQL *conn;
    char name[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter your name: ");
    fgets(name, BUFFER_SIZE, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter your password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = '\0';

    hash_password(password, hashed_password);

    char query[BUFFER_SIZE * 2];
    snprintf(query, sizeof(query), "INSERT INTO users (name, password) VALUES ('%s', '%s')",
             name, hashed_password);

    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    printf("Registration successful.\n");
    
    mysql_close(conn);

    return 0;
}
