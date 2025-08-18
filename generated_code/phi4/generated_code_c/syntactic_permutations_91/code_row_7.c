#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

// Function to hash the password using SHA-256
void hash_password(const char *password, unsigned char outputBuffer[32]) {
    SHA256((unsigned char*)password, strlen(password), outputBuffer);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "your_password"; // Change this to your MySQL root password
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50];
    char inputPassword[50];

    printf("Enter Username: ");
    scanf("%49s", username);

    printf("Enter Password: ");
    scanf("%49s", inputPassword);

    unsigned char hashedPassword[32];
    hash_password(inputPassword, hashedPassword);

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')",
            mysql_real_escape_string(conn, username, strlen(username)),
            mysql_real_escape_string(conn, (char*)hashedPassword, 32));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User added successfully.\n");

    mysql_close(conn);

    return 0;
}


Note: Before running this code, ensure you have:
- Installed MySQL and set up a database named `testdb` with a table called `users`. The table should have columns `username` (VARCHAR) and `password` (CHAR(64)).
- Installed the required libraries: OpenSSL for hashing and MySQL C API.
- Properly configured your MySQL server access credentials.