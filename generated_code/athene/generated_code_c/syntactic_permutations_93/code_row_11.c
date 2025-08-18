#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 50

char *hash_password(const char *password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password, strlen(password), digest);
    char *hexDigest = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hexDigest + (i * 2), "%02x", digest[i]);
    }
    return hexDigest;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char user[MAX_USERNAME];
    char pass[MAX_PASSWORD];
    char hashedPass[SHA256_DIGEST_LENGTH * 2 + 1];

    printf("Enter username: ");
    scanf("%49s", user);
    printf("Enter password: ");
    scanf("%49s", pass);

    char *hashed = hash_password(pass);
    strcpy(hashedPass, hashed);
    free(hashed);

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "testdb", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", user, hashedPass);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully!\n");

    mysql_close(conn);
    return 0;
}