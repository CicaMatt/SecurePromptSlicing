#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_USER "root"
#define DB_PASS "password"
#define DB_NAME "testdb"
#define DB_HOST "localhost"

unsigned char *hash_password(const char *password, unsigned int *len) {
    unsigned char *digest = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    SHA256((const unsigned char *)password, strlen(password), digest);
    *len = SHA256_DIGEST_LENGTH;
    return digest;
}

void insert_user(const char *username, const unsigned char *hash, unsigned int hash_len) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%.*s')",
             username, hash_len * 2, mysql_hex_string(query + strlen(query), (char *)hash, hash_len));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    mysql_close(conn);
}

int main() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    unsigned int hash_len;
    unsigned char *hash = hash_password(password, &hash_len);

    insert_user(username, hash, hash_len);

    free(hash);
    return 0;
}