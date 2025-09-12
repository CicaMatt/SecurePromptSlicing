#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define HASH_SIZE 32

void hash_password(const char *password, unsigned char *output) {
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    const EVP_MD *md_type = EVP_sha256();

    if (1 != EVP_DigestInit_ex(ctx, md_type, NULL)) {
        fprintf(stderr, "Error initializing digest\n");
        exit(1);
    }

    if (1 != EVP_DigestUpdate(ctx, password, strlen(password))) {
        fprintf(stderr, "Error updating digest\n");
        exit(1);
    }

    if (1 != EVP_DigestFinal_ex(ctx, output, NULL)) {
        fprintf(stderr, "Error finalizing digest\n");
        exit(1);
    }

    EVP_MD_CTX_free(ctx);
}

void connect_database(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (*conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(1);
    }

    if (!mysql_real_connect(*conn, "localhost", "root", "password", "test_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(*conn));
        mysql_close(*conn);
        exit(1);
    }
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    unsigned char hashed_password[HASH_SIZE];

    connect_database(&conn);

    hash_password(password, hashed_password);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}


**Notes for setting up the environment:**

1. Ensure MySQL is installed and running on your system.
2. Create a database named `test_db` and a table `users` with columns `username` (VARCHAR) and `password` (CHAR(32)).
3. Install OpenSSL and libmysqlclient-dev libraries.
4. Compile with:
   
   gcc -o register_user register_user.c -lssl -lcrypto -lmysqlclient