#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "testdb"
#define DB_HOST "localhost"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char *)password, strlen(password), output);
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char username[50];
    char password[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    char hex_password[2 * SHA256_DIGEST_LENGTH + 1];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    hash_password(password, hashed_password);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_password + (i * 2), "%02x", hashed_password[i]);
    }

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hex_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return 0;
}