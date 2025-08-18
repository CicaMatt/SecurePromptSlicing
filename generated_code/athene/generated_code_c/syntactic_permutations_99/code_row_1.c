#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "testdb"

unsigned char *hash_password(const char *password, unsigned int *len) {
    unsigned char *digest = (unsigned char *)malloc(SHA256_DIGEST_LENGTH);
    SHA256((const unsigned char *)password, strlen(password), digest);
    *len = SHA256_DIGEST_LENGTH;
    return digest;
}

void hexencode(const unsigned char *data, size_t len, char *output) {
    static const char *hex = "0123456789abcdef";
    for (size_t i = 0; i < len; ++i) {
        output[i*2] = hex[data[i] >> 4];
        output[i*2 + 1] = hex[data[i] & 0xf];
    }
    output[len * 2] = '\0';
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[50], password[50];
    unsigned int hash_len;
    unsigned char *hash;
    char hex_hash[SHA256_DIGEST_LENGTH * 2 + 1];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash = hash_password(password, &hash_len);
    hexencode(hash, hash_len, hex_hash);
    free(hash);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hex_hash);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return 0;
}