#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main(void)
{
    // Connect to database
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "users", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Get username and password from user
    char *username = malloc(256);
    printf("Enter your username: ");
    fgets(username, 256, stdin);

    char *password = malloc(256);
    printf("Enter your password: ");
    fgets(password, 256, stdin);

    // Hash the password using SHA-256 algorithm
    unsigned char hash[32];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);

    // Insert data into database
    char query[1024];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hash);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully!\n");

    // Clean up
    free(username);
    free(password);
    mysql_close(conn);

    return 0;
}