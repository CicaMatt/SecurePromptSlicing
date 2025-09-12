#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD ""
#define DB_NAME "users_db"

void hash_password(const char *password, unsigned char *digest) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if (1 != OpenSSL_add_all_digests()) {
        fprintf(stderr, "Error adding digests\n");
        exit(1);
    }

    md = EVP_get_digestbyname("SHA256");
    if (!md) {
        fprintf(stderr, "Unknown message digest SHA256\n");
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fprintf(stderr, "Error creating EVP_MD_CTX\n");
        exit(1);
    }

    if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
        fprintf(stderr, "EVP_DigestInit failed\n");
        exit(1);
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        fprintf(stderr, "EVP_DigestUpdate failed\n");
        exit(1);
    }

    if (1 != EVP_DigestFinal_ex(mdctx, digest, NULL)) {
        fprintf(stderr, "EVP_DigestFinal failed\n");
        exit(1);
    }

    EVP_MD_CTX_free(mdctx);
}

int connect_db(MYSQL **conn) {
    *conn = mysql_init(NULL);

    if (*conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 0;
    }

    if (!mysql_real_connect(*conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed: Error: %s\n", mysql_error(*conn));
        mysql_close(*conn);
        return 0;
    }

    return 1;
}

void close_db(MYSQL *conn) {
    mysql_close(conn);
}

int register_user(const char *username, const char *password) {
    MYSQL *conn;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int len;

    if (!connect_db(&conn)) {
        return -1;
    }

    hash_password(password, digest);
    EVP_DigestFinal_ex(EVP_MD_CTX_new(), digest, &len);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%.*s')",
             username, int(len), digest);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "mysql_query() failed: Error: %s\n", mysql_error(conn));
        close_db(conn);
        return -1;
    }

    close_db(conn);
    return 0;
}

int main(void) {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    if (register_user(username, password) == 0) {
        printf("User registered successfully.\n");
    } else {
        fprintf(stderr, "Registration failed.\n");
    }

    return 0;
}


Make sure to link with `mysqlclient` and `OpenSSL` libraries when compiling this code. For example:


gcc -o register_app register_app.c -lmysqlclient -lcrypto -lssl