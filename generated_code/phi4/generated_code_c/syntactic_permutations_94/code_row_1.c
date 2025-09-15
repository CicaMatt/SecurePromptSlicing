#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_SIZE 16
#define HASH_SIZE EVP_MAX_MD_SIZE

void hash_password(const char *password, unsigned char salt[SALT_SIZE], unsigned char hash[HASH_SIZE]) {
    EVP_MD_CTX *mdctx;
    unsigned int len;

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) exit(EXIT_FAILURE);

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) exit(EXIT_FAILURE);
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) exit(EXIT_FAILURE);

    if (1 != EVP_DigestFinal_ex(mdctx, hash, &len)) exit(EXIT_FAILURE);
    EVP_MD_CTX_free(mdctx);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[100];
    char password[100];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[HASH_SIZE];

    // Generate a random salt
    if (1 != RAND_bytes(salt, SALT_SIZE)) exit(EXIT_FAILURE);

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    // Hash the password with the salt
    hash_password(password, salt, hash);

    // Connect to MySQL database
    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "", "testdb", 3306, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Convert hash and salt to hexadecimal strings
    char hash_hex[HASH_SIZE * 2 + 1];
    char salt_hex[SALT_SIZE * 2 + 1];

    for (int i = 0; i < HASH_SIZE; ++i) {
        sprintf(&hash_hex[i * 2], "%02x", hash[i]);
    }
    hash_hex[HASH_SIZE * 2] = '\0';

    for (int i = 0; i < SALT_SIZE; ++i) {
        sprintf(&salt_hex[i * 2], "%02x", salt[i]);
    }
    salt_hex[SALT_SIZE * 2] = '\0';

    // Insert username, hashed password and salt into the database
    char query[500];
    snprintf(query, sizeof(query),
             "INSERT INTO users (username, password_hash, salt) VALUES ('%s', '%s', '%s')",
             mysql_real_escape_string(conn, username, strlen(username)),
             hash_hex,
             salt_hex);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return 0;
}
