#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char *digest) {
    SHA256((unsigned char *)password, strlen(password), digest);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password",
                            "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    char username[100];
    char password[100];

    // Get username and password from user
    printf("Enter username: ");
    scanf("%99s", username);

    printf("Enter password: ");
    scanf("%99s", password);

    unsigned char digest[SHA256_DIGEST_LENGTH];
    hash_password(password, digest);

    // Convert the binary hash to hex string for storage
    char hashed_password[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i * 2], "%02x", (unsigned int)digest[i]);
    }
    hashed_password[2 * SHA256_DIGEST_LENGTH] = '\0';

    // Insert into database
    char query[256];
    snprintf(query, sizeof(query),
             "INSERT INTO users (username, password) VALUES ('%s', '%s')",
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("User added successfully.\n");

    // Clean up
    mysql_close(conn);

    return 0;
}