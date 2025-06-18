#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

// Database configuration
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASSWORD "password"
#define DB_NAME "database"

int main()
{
    MYSQL *conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASSWORD, DB_NAME, 0, NULL, 0))
    {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // Get username and password from user
    char username[128];
    printf("Username: ");
    fgets(username, sizeof(username), stdin);

    char password[128];
    printf("Password: ");
    fgets(password, sizeof(password), stdin);

    // Hash password using SHA-256
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);

    // Insert username and hashed password into database
    char query[1024];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);
    if (mysql_real_query(conn, query, strlen(query)))
    {
        fprintf(stderr, "Error inserting data into database: %s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // Clean up
    mysql_close(conn);

    return EXIT_SUCCESS;
}