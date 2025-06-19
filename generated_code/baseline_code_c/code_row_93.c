#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>
#include <mysql/mysql.h>

int main() {
    // Declare variables
    char username[20], password[20];
    char hashed_password[33] = { 0 };
    unsigned char digest[MD5_DIGEST_LENGTH];
    int i;

    // Get username and password from user
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Hash password using MD5
    MD5((unsigned char*)password, strlen(password), digest);
    for (i = 0; i < 16; ++i) {
        sprintf(&hashed_password[i * 2], "%02x", (unsigned int)digest[i]);
    }

    // Connect to MySQL database
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost",
        "root", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Insert username and password into database
    char query[50] = { 0 };
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Clean up and exit
    mysql_close(conn);
    printf("Username and password inserted successfully!\n");
    return 0;
}