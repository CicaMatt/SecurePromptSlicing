#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

// Function to hash the password using SHA-256
void hash_password(const char *password, unsigned char hashedPassword[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashedPassword, &sha256);
}

// Function to convert binary data to hex string
void bin_to_hex(const unsigned char *binData, char *hexString, size_t binSize) {
    for (size_t i = 0; i < binSize; i++) {
        sprintf(hexString + (i * 2), "%02x", binData[i]);
    }
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[50], password[50];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    char hexHashedPassword[SHA256_DIGEST_LENGTH * 2 + 1];

    // Connect to the database
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "", "user_database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    // Hash the password
    hash_password(password, hashedPassword);
    bin_to_hex(hashedPassword, hexHashedPassword, SHA256_DIGEST_LENGTH);
    hexHashedPassword[SHA256_DIGEST_LENGTH * 2] = '\0';

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hexHashedPassword);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    // Close connection
    mysql_close(conn);

    return 0;
}