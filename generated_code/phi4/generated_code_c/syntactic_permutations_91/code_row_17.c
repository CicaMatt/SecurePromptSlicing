#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (!EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        perror("DigestInit");
        exit(1);
    }
    if (!EVP_DigestUpdate(mdctx, password, strlen(password))) {
        perror("DigestUpdate");
        exit(1);
    }
    unsigned int len = 0;
    if (!EVP_DigestFinal_ex(mdctx, output, &len)) {
        perror("DigestFinal");
        exit(1);
    }
    EVP_MD_CTX_free(mdctx);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50];
    char password[100];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char query[200];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%.*s')",
             username, SHA256_DIGEST_LENGTH, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return 0;
}


Note: Before running this code:
- Ensure that the MySQL server is running and accessible with appropriate credentials.
- Create a database named `testdb` and a table named `users` with columns `username` (VARCHAR) and `password` (CHAR(64)) to store hashed passwords.
- Install necessary libraries such as OpenSSL for hashing, and MySQL client library (`libmysqlclient-dev`). Compile the code using gcc with `-lssl -lcrypto -lmysqlclient`.