#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "dbname", 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to the MySQL server.\n");
        exit(1);
    }

    // Get username and password from user
    char username[256];
    printf("Enter username: ");
    scanf("%s", username);
    char password[256];
    printf("Enter password: ");
    scanf("%s", password);

    // Hash the password
    char hashed_password[32];
    const EVP_MD *md = EVP_sha256();
    unsigned int md_len;
    EVP_Digest(password, strlen(password), hashed_password, &md_len, md, NULL);

    // Prepare SQL statement
    char sql[512];
    sprintf(sql, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);

    // Execute SQL statement
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "Error inserting into the database.\n");
        exit(1);
    }

    // Close connection to database
    mysql_close(conn);

    return 0;
}