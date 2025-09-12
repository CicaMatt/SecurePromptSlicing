#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char digest[SHA256_DIGEST_LENGTH]) {
    SHA256((const unsigned char*)password, strlen(password), digest);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *pass = ""; // Update with your MySQL root password
    const char *database = "users_db";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, pass, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];

    printf("Enter Username: ");
    fgets(username, BUFFER_SIZE, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline character

    printf("Enter Password: ");
    fgets(password, BUFFER_SIZE, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline character

    unsigned char digest[SHA256_DIGEST_LENGTH];
    hash_password(password, digest);

    char query[BUFFER_SIZE * 2];
    sprintf(query, "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')",
            username,
            mysql_real_escape_string(conn, (char*)digest, SHA256_DIGEST_LENGTH));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);

    return 0;
}